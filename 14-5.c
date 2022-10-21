#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
int main(int argc,char *argv[])
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    int fp[2];
    int fp2[2];
    fp[0] = open(argv[1], O_RDWR);
    FILE *f1;
    FILE *f2;
    FILE *f3;
    //struct stat buf;
    //stat(argv[1], &buf);
    //int size = buf.st_size;
    //printf("SIZE: %d\n", size);
    for(int i = 2; i < argc; i++) {

        f1 = fdopen(fp[0], "r");
        pipe(fp);
        f2 = fopen(argv[i], "r");
        f3 = fdopen(fp[1], "w");
        printf("we read from %d, %s TO %d: \n", fp[0], argv[i], fp[1]);
        fflush(stdout);
        if(!(fork())) {
        setbuf(stdin, NULL);
        setbuf(stdout, NULL);

        setbuf(f1, NULL);
        setbuf(f2, NULL);
        setbuf(f3, NULL);
        printf("ONE\n");
        fflush(stdout);
            int x1,x2,x;
        int count = 10;
            while((fscanf(f1, "%d", &x1)) > 0 && (fscanf(f2, "%d", &x2) > 0)){

printf("INDEX   %d    SIMILAR:: %d\n", i,x1);
printf("ID  ==  %d    x1:  %d   ----    x2:  %d\n\n", i,x1,x2);
                if(x1 == x2) {
                    fprintf(f3, "%d ", x1);
                    printf("OUTn: %d\n\n", x1);
                    fflush(stdout);
                } else {
                    while(x1 > x2 && (fscanf(f2, "%d", &x2) > 0)) {
                    printf("ID: %d x2 > x1 ::::%d ", i, x2);
                    }
                    printf("\n");
                    while(x1 < x2 && count > 0 && (fscanf(f1, "%d", &x1) > 0) ) {
                    printf("ID:  %d x1 < x2 ::::%d -- %d  ", i, x1,x2);
                    fflush(stdout);
                    }
                    printf("OOOUUTT\n");
                    fflush(stdout);
                    printf("\n");
                    if(x1 == x2) {
                        fprintf(f3, "%d ", x1);
                        printf("OUTn: %d\n\n", x1);
                    }
                }

            }
            printf("BBBRREEEAAAKKK %d ", i);

            printf("==\n");

            _exit(0);

        }
    }
    printf("  1111*\n");
    while(wait(NULL) >= 0);
    printf("  *\n");
    int x;
    while((fscanf(f3, "%d", &x)) > 0) {
        printf("%d\n",  x);
        fflush(stdout);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    close(fp[0]);
    close(fp[1]);
    return 0;
}
