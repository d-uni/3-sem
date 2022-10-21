#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
int
main(void)
{
    int pfd[2];
    pipe(pfd);
    pid_t pid1, pid2;
    int a;
    if(!(pid1 = fork())) {
        if(!(pid2 = fork())) {
            close(pfd[1]);
            int x = 0;
            long long int s = 0;
            while(read(pfd[0], &x, sizeof(x))) {
                s = s + x;
            }
            close(pfd[0]);
            printf("%lld\n", s);
            fflush(stdout);
            _exit(0);
        }
        close(pfd[1]);
        close(pfd[0]);
        wait(NULL);
        _exit(0);
    }
    close(pfd[0]);
    while(scanf("%d", &a) == 1) {
        write(pfd[1], &a, sizeof(a));
    }
    close(pfd[1]);
    wait(NULL);
    return 0;
}
