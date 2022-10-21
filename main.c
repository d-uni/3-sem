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
struct Msgp
{
    long msgtype;
    int64_t msgtext[2];
};
int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    int f = 0;
    int key = atoi(argv[1]);
    int n = atoi(argv[2]);
    int64_t value1 = strtoll(argv[3], NULL, 10);
    int64_t value2 = strtoll(argv[4], NULL, 10);
    int64_t maxval = strtoll(argv[5], NULL, 10);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    int semid = semget(key, n, 0600 | IPC_CREAT);
    struct Msgp msgpp;
    msgpp.msgtype = 1;
    int pid;
    msgpp.msgtext[0] = value1;
    msgpp.msgtext[1] = value2;
    msgsnd(msgid, &msgpp, sizeof(msgpp.msgtext[2]), 0);
    for (int i = 0; i < n; i++) {
        if(!(pid = fork())) {
            while(semop(semid, (struct sembuf[]) {{i, -1, 0}}, 1) >= 0) {
                int er = msgrcv(msgid, &msgpp, 2 * sizeof(int64_t), 1, 0);
                if(er == -1) {
                    semctl(semid, 0 , IPC_RMID);
                    msgctl(msgid, IPC_RMID, NULL);
                    break;
                }
                int64_t x1 = msgpp.msgtext[0];
                int64_t x2 = msgpp.msgtext[1];
                int64_t x3 = x1 + x2;
                msgpp.msgtext[0] = x2;
                msgpp.msgtext[1] = x3;
                er = msgsnd(msgid, &msgpp, 2 * sizeof(int64_t), 0);
                if(er == -1) {
                    semctl(semid, 0 , IPC_RMID);
                    msgctl(msgid, IPC_RMID, NULL);
                    break;
                }
                printf("%d %lld\n", i, x3);
                fflush(stdout);
                if(x3 > maxval || x3 < -maxval) {
                        semctl(semid, 0 , IPC_RMID);
                        msgctl(msgid, IPC_RMID, NULL);
                        break;
                    }
                semop(semid, (struct sembuf[]) {{x3 % n, 1, 0}}, 1);
                }
            exit(0);
        } else if(pid == -1) {
            f = 1;
            semctl(semid, 0 , IPC_RMID);
            msgctl(msgid, IPC_RMID, NULL);
        }
    }
    semop(semid, (struct sembuf[]) {{0, 1, 0}}, 1);
    while (wait(NULL) >= 0);
    if(f == 1) {
        return 1;
    }
    return 0;
}
