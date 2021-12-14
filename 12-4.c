/* Родитель создает двух сыновей, связывая их каналом. Сыновья начинают обмениваться числами 1, 2, 3, ... Число 1 получает первый сын. При получении числа из входного канала каждый сын печатает на стандартный поток вывода родителя свой номер (1 или 2) и полученное число и пересылает обратно число, на 1 большее. При достижении числа, задаваемого в командной строке, пересылает то же самое число в канал и завершает работу.

Процесс должен завершить работу при получении максимального числа из канала. Завершать процесс в других случаях не разрешается. Запрещается отправлять сигнал отцу.

Отец дожидается завершения работы обоих процессов, затем выводит строку Done и завершает работу.

Если в командной строке передано число 5, pid первого процесса - 100, pid второго процесса - 101, то вывод должен быть таким:

1 1
2 2
1 3
2 4
Done

Данные передавать в текстовом виде, для ввода-вывода использовать высокоуровневый ввод-вывод (printf, scanf).

Для синхронизации использовать единственный сигнал SIGUSR1. PID процессов передавать через канал.

Привязывать файловые дескрипторы к дескрипторам потока можно либо с помощью функции fdopen, либо с помощью перенаправления стандартных потоков ввода-вывода.

Какие-либо средства взаимодействия, кроме одного канала и сигнала SIGUSR1 использовать запрещено. signalfd использовать запрещено. */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int N;
int pfd1[2];
FILE *file10;
FILE *file11;
void handler(int s)
{
    signal(SIGUSR1, handler);
    int x, pi1, pi2;
    fscanf(file10, "%d", &pi1);
    fscanf(file10, "%d", &x);
    fscanf(file10, "%d", &pi2);
    if (pi1 < pi2) {
        if(x >= N) {
            fprintf(file11, "%d ", pi2);
            x++;
            fprintf(file11, "%d ", x);
            fprintf(file11, "%d ", pi1);
            kill(pi2, SIGUSR1);
            _exit(0);
        } else {
            printf("1 %d\n",x); fflush(stdout);
            ++x;
            fprintf(file11, "%d ", pi2);
            fprintf(file11, "%d ", x);
            fprintf(file11, "%d ", pi1);
            kill(pi2, SIGUSR1);
        }
    } else if(pi1 > pi2){
        if(x >= N) {
            fprintf(file11, "%d ", pi2);
            x++;
            fprintf(file11, "%d ", x);
            fprintf(file11, "%d ", pi1);
            kill(pi2, SIGUSR1);
            _exit(0);
        } else {
            printf("2 %d\n",x); fflush(stdout);
            ++x;
            fprintf(file11, "%d ", pi2);
            fprintf(file11, "%d ", x);
            fprintf(file11, "%d ", pi1);
            kill(pi2, SIGUSR1);
        }
    }
}
int
main(int argc,  char *argv[])
{
    pid_t pid1, pid2;
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    signal(SIGUSR1, handler);
    pipe(pfd1);
    file10 = fdopen(pfd1[0], "r");
    file11 = fdopen(pfd1[1], "w");
    setbuf(file10, NULL);
    setbuf(file11, NULL);
    int z = 1;
    N = atoi(argv[1]);
    if (!(pid1 = fork())) {
        setbuf(file10, NULL);
        setbuf(file11, NULL);
        while (1) pause();
        return 0;
    } else if (!(pid2 = fork())) {
        setbuf(file10, NULL);
        setbuf(file11, NULL);
        while (1) pause();
        return 0;
    }
    fprintf(file11, "%d ", pid1);
    fprintf(file11, "%d ", z);
    fprintf(file11, "%d ", pid2);
    kill(pid1, SIGUSR1);
    close(pfd1[0]);
    close(pfd1[1]);
    fclose(file10);
    fclose(file11);
    wait(NULL);
    wait(NULL);
    printf("Done\n");
    return 0;
}
