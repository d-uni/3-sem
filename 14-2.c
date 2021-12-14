/* Программе в аргументах командной строки задаются:

    Размер массива (count);
    Ключ IPC (key);
    Количество процессов (nproc);
    Число итераций (iter_count);
    Затравка ГПСЧ для каждого процесса (nproc аргументов).

Программа должна создать в разделяемой памяти массив из count элементов типа int и заполнить его значениями, считанными со стандартного потока ввода.

Далее программа должна создать nproc процессов, для каждого процесса проинициализировав ГПСЧ соответствующим значением из командной строки.

Все процессы должны выполнить iter_count итераций модификации массива по следующему алгоритму. На каждой итерации выбираются два случайных индекса в массиве (каждый индекс в диапазоне [0;count) ) и случайное значение в диапазоне [0; 10). Далее должна вызываться функция operation, которая выполняет следующие действия: 
Считайте эту функцию написанной и доступной в вашей программе.

Родитель дожидается окончания всех сыновей и выводит на стандартный поток вывода значения массива.

Должна быть обеспечена целостность массива.

Синхронизация должна позволять двум процессам одновременно модифицировать массив, если модифицируемые индексы массива не пересекаются.

    Процессы, SysV семафоры (sys/sem), SysV разделяемая память (sys/shm).
    Процессы, SysV семафоры, mmap.
    Нити, mutex.

Второй аргумент командной строки не используется, если программа не использует SysV IPC.

Другие варианты использовать запрещено.

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
void
operation(int *data, int ind1, int ind2, int value)
{
    if (ind1 != ind2) {
        int tmp1 = data[ind1] - value;
        int tmp2 = data[ind2] + value;

        data[ind1] = tmp1;
        data[ind2] = tmp2;
    }
}
int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    long long int count = atoll(argv[1]), key = atoll(argv[2]), nproc = atoll(argv[3]);
    long long int iter_count = atoll(argv[4]);
    int *rng = (int *)malloc(nproc * sizeof(int));
    for(int i = 0; i < nproc; i++) {
        rng[i] = atoi(argv[i + 5]);
    }
    int semid = semget(key, count, 0600 | IPC_CREAT);
    int *pmem = NULL;
    int shmid = shmget(key, count * sizeof(*pmem), 0600 | IPC_CREAT);
    pmem = shmat(shmid, NULL, 0);
    int x = 0;
    for(int i = 0; i < count; i++) {
        scanf("%d", &x);
        *(pmem + i) = x;
        semop(semid, (struct sembuf[]) {{i,1,0}}, 1);
    }
    for (int i = 0; i < nproc; i++) {
        if(!(fork())) {
            srand(rng[i]);
            int index1;
            int index2;
            int val;
            for(int j = 0; j < iter_count; j++) {
                index1 = rand() % count;
                index2 = rand() % count;
                val = rand() % 10;
                if(index1 != index2) {
                    semop(semid, (struct sembuf[]) {{index2,-1,0},{index1,-1,0}}, 2);
                    operation(pmem, index1, index2, val);
                    semop(semid, (struct sembuf[]) {{index2,1,0},{index1,1,0}}, 2);
                } else {
                    semop(semid, (struct sembuf[]) {{index2,-1,0}}, 1);
                    operation(pmem, index1, index2, val);
                    semop(semid, (struct sembuf[]) {{index2,1,0}}, 1);
                }
            }
            exit(0);
        }

    }
    while (wait(NULL) >= 0);
    for(int i = 0; i< count; i++) {
        printf("%d\n", pmem[i]);
    }
    semctl(semid, 0 , IPC_RMID);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
