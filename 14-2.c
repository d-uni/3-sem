#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
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
                semop(semid, (struct sembuf[]) {{index2,-1,0},{index1,-1,0}}, 1);
                operation(pmem, index1, index2, val);
                semop(semid, (struct sembuf[]) {{index2,1,0},{index1,1,0}}, 1);
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
