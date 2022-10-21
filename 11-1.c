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
main()
{
    int pfd[2];
    pipe(pfd);
    pid_t pid1, pid2, pid3;
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    if(!(pid1 = fork())) {
        setbuf(stdout, NULL);
        setbuf(stdin, NULL);
        if(!(pid3 = fork())) {
            setbuf(stdout, NULL);
            setbuf(stdin, NULL);
            if(!(pid2 = fork())) {
                setbuf(stdout, NULL);
                setbuf(stdin, NULL);
                close(pfd[0]);
                struct tm *time_inf;
                time_t res;
                res = time(NULL);
                time_inf = localtime( &res );
                write(pfd[1], &time_inf -> tm_mday, sizeof(time_inf -> tm_mday));
                write(pfd[1], &time_inf -> tm_mon, sizeof(time_inf -> tm_mon));
                write(pfd[1], &time_inf -> tm_year, sizeof(time_inf -> tm_year));
                close(pfd[1]);
                exit(0);
            }
            int z;
            close(pfd[1]);
            wait(NULL);
            read(pfd[0], &z, sizeof(z));

            printf("D:%02d\n", z);
            close(pfd[0]);
            exit(0);
        }
        close(pfd[1]);
        int x;
        wait(NULL);
        read(pfd[0], &x, sizeof(x));
        printf("M:%02d\n", x + 1);
        close(pfd[0]);
        exit(0);
    }
    close(pfd[1]);
    int y;
    wait(NULL);
    read(pfd[0], &y, sizeof(y));
    printf("Y:%04d\n", y + 1900);
    close(pfd[0]);
    return 0;
}
