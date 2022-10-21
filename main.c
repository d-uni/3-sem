#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#inclusde <signals.h>
volatile sig_atomic_t sig = 0;
void hnd(int stat)
{
    sig_atomic_t sig = 1;
}
char *pids;
int size = 0;
int
main(int argv, char *argc[])
{
    signal(SIGKILL, hnd);
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    int fdp[2];
    int x = pipe(fdp);
    if(x == -1) {
        _exit(1);
    }
    pid_t pid;
    for(int i = 1; i < argv && sig_atomic_t sig == 0; i++) {
        if(!(pid = fork())) {
        setbuf(stdin, NULL);
        setbuf(stdout, NULL);
        if(i == 1) {

            dup2(fd[1], 1);
        } else if(i == argv - 1) {
            dup2(fd[0], 0);
        } else {
            dup2(fd[1], 1);
            dup2(fd[0], 0);
        }
        close(fd[1]);
        close(fd[0]);
        execlp(argc[i], argc[i], NULL);
        _exit(1);
        } else if(pid == -1){
            hnd(1);
            for(int j = 0; j < size; j++) {
                kill(pids[j], SIGKILL);
                waitpid(pids[j], NULL);
            }
            _exit(1);
        } else {
            char *p = calloc(1, sizeof(int));
            p = &pid;
            pids[sizeof(pids) + 1] = p;

        }

    }
    while((waitstatus = wait(NULL)) > 0) {}
    printf("Hello world!\n");
    return 0;
}
