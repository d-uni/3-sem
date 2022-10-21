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
main(int argc,  char *argv[])
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    int pfd1[2];
    pipe(pfd1);
    int pfd2[2];
    pipe(pfd2);
    pid_t pid1, pid2;
    int x = 1;
    FILE *file10 = fdopen(pfd1[0], "r");
    FILE *file11 = fdopen(pfd1[1], "w");
    FILE *file20 = fdopen(pfd2[0], "r");
    FILE *file21 = fdopen(pfd2[1], "w");
    fprintf(file11, "%d ", x);
    int max;
    max = atoi(argv[1]);
    if(!(pid1 = fork())) {
        setbuf(file21, NULL);
        close(pfd1[1]);
        close(pfd2[0]);
        int a;
        while((fscanf(file10, "%d", &a))) {
            if(a > max - 1) {
                close(pfd1[0]);
                close(pfd2[1]);
                _exit(0);
            }
            printf("1 %d\n", a);
            fflush(stdout);
            a++;
            fprintf(file21, "%d ", a);
            fflush(file21);
        }
        close(pfd1[0]);
        close(pfd2[1]);
        _exit(0);
    }
    if(!(pid2 = fork())) {
        setbuf(file11, NULL);
        close(pfd1[0]);
        close(pfd2[1]);
        int a;
        while((fscanf(file20, "%d", &a))) {
            if(a > max - 1) {
                close(pfd2[0]);
                close(pfd1[1]);
                _exit(0);
            }
            printf("2 %d\n", a);
            fflush(stdout);
            a++;
            fprintf(file11, "%d ", a);
            fflush(file11);
        }
        close(pfd1[1]);
        close(pfd2[0]);
        _exit(0);
    }
    close(pfd1[0]);
    close(pfd2[1]);
    close(pfd1[1]);
    close(pfd2[0]);
    fclose(file10);
    fclose(file11);
    fclose(file20);
    fclose(file21);
    wait(NULL);
    wait(NULL);
    printf("Done\n");
    return 0;
}
