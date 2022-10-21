#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
    setbuf(stdin, NULL);
    int fd = creat("a.txt", 0666);
    int key = ftok("a.txt", 1);
    int n = atoi(argv[1]);
    int semid = semget(key, n, 0600 | IPC_CREAT);
    for (int i = 0; i < n; i++) {
        if(!(fork())) {
            char a[12] = {};
            int x;
            while(semop(semid, (struct sembuf[]) {{i, -1, 0 }}, 1) >= 0) {

                if(scanf("%s", a) != EOF){
                    x = atoi(a);
                    memset(a, 0, strlen(a));
                    printf("%d %d\n", i, x);
                    fflush(stdout);
                    semop(semid, (struct sembuf[]) {{(n + (x % n)) % n, 1, 0}}, 1);
                } else {
                    semctl(semid, 0, IPC_RMID);
                    break;
                }
            }
            exit(0);
        }
    }
    semop(semid, (struct sembuf[]) {{0,1,0}}, 1);
    while (wait(NULL) >= 0);
    close(fd);
    return 0;
}
