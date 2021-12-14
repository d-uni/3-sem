/*Problem up12-3: mz12-3 (дореш)

В аргументах командной строки процессу передается число N и имена текстовых файлов. Каждый текстовый файл должен содержать одну строку —имя исполняемого файла. Процесс запускает на параллельное исполнение не более чем первые N исполняемых файлов и после окончания параллельного исполнения на последовательное исполнение —оставшиеся исполняемые файлы. По окончанию работы процесс-родитель выводит на экран число — количество потомков, которые были успешно запущены и завершили свою работу с пользовательским кодом 0.

Единственная строка каждого текстового файла содержит символ '\n' в конце. В строке отсутствуют пробельные символы, кроме финального '\n'.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <limits.h>

int
main(int argc, char *argv[])
{

    int count = argc;
    int i, j;
    int pid, pids = 0;
    int N = atoi(argv[1]) + 2;
    int answ = 0;
    int *pidarr = calloc(N - 2, sizeof(int *));
    for(i = 2; i < N && i < count; i++) {
        if(!(pid = fork())) {
            FILE *fil = fopen(argv[i], "r");
            char exe[PATH_MAX + 1];
            fscanf(fil, "%s", exe);
            execlp(exe, exe, NULL);
            _exit(1);
        } else if(pid > 0) {
            pids++;
            pidarr[i - 2] = pid;
        }
    }
    int st;
    for(j = 0; j < pids; j++) {
        if(pidarr[j] > 0) {
            waitpid(pidarr[j], &st, 0);
            if(WIFEXITED(st) != 0 && WEXITSTATUS(st) == 0) {
                answ++;
            }
        }
    }
    for(j = i; j < count; j++) {
        if(!(pid = fork())) {
            FILE *fil = fopen(argv[j], "r");
            char exe[PATH_MAX + 1];
            fscanf(fil, "%s", exe);
            execlp(exe, exe, NULL);
            _exit(1);
        } else if(pid > 0) {
            int status;
            wait(&status);
            if(WIFEXITED(status) != 0 && WEXITSTATUS(status) == 0) {
                answ++;
            }
        }
    }
    printf("%d\n", answ);
    return 0;
}
