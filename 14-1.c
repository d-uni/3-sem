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
    int nproc = atoi(argv[1]), key = atoi(argv[2]), maxval = atoi(argv[3]);
    int semid = semget(key, nproc + 1, 0600 | IPC_CREAT);
    int *pmem = NULL;
    int shmid = shmget(key, 2 * sizeof(*pmem), 0600 | IPC_CREAT);
    pmem = shmat(shmid, NULL, 0);
    *pmem = 0;
    *(pmem + 1) = 0;
    for (int i = 1; i < nproc + 1; i++) {
        if(!(fork())) {
            while(semop(semid, (struct sembuf[]) {{i, -1, 0 }}, 1) >= 0) {
                printf("%d %d %d\n", i, (*pmem)++, pmem[1]);
                fflush(stdout);
                *(pmem + 1) = i;
                if(*pmem > maxval) {
                    semctl(semid, 0 , IPC_RMID);
                    shmctl(shmid, IPC_RMID, NULL);
                    break;
                }
                semop(semid, (struct sembuf[])
                {{((*pmem%nproc)*(*pmem%nproc)*(*pmem%nproc)*(*pmem%nproc))%nproc+1, 1, 0}},
                    1);
            }
            exit(0);
        }

    }
    semop(semid, (struct sembuf[]) {{1,1,0}}, 1);
    while (wait(NULL) >= 0);
    return 0;
}
