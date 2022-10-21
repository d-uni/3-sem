#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid, pid2;
    int flaf = 0;
    if((pid = fork())<0) {
    return -1;
    } else if(!pid) {
        oooo:
        printf("HEAR  ");
        if((pid2 = fork())<0) {
            return -1;
        } else if(!pid2) {
             int x;
             scanf("%d", &x);
            if(x==0) {
            printf("NULL  ");
                exit(0);
            } else {
            printf("goto  ");
                goto oooo;
                printf("after   ");
                wait(NULL);
                printf("%d*  ", x);
                exit(0);
                }
            }
        wait(NULL);
        printf("+");
        exit(0);
    }
    wait(NULL);

    printf("Hello world!\n");
    exit(0);
}
