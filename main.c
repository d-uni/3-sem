#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
int main(int argc,char *argv[])
{
    double left = strtod(argv[1], NULL);
    double right = strtod(argv[2], NULL);
    int n = atoi(argv[3]);
    double dx = (left - right) / n;
    double out = 0;

    int fd = open("au.c", O_CREAT | O_WRONLY | O_TRUNC, 0777);
    char buf1[] = "#include <stdio.h>\n#include <math.h>\nint main(void){double left = ";
    write(fd, buf1, strlen(buf1));
    write(fd, argv[1], strlen(argv[1]));
    char buf2[] = ";\ndouble right = ";
    write(fd, buf2, strlen(buf2));
    write(fd, argv[2], strlen(argv[2]));
    char buf3[] = ";\ndouble x=0;\ndouble si=0;\nfor(int i = 0;i<";
    write(fd, buf3, strlen(buf3));
    write(fd, argv[3], strlen(argv[3]));
    char buf5[] = "; i++)\n{ x = left + i * (right - left);\ndouble si =";
    write(fd, buf5, strlen(buf5));
    write(fd, argv[4], strlen(argv[4]));
    char buf4[] = ";\nprintf(\"%lf \", si);}\nreturn 0;\n}";
    write(fd, buf4, strlen(buf4));


    int pd[2];
    pipe(pd);
    if(!(fork())) {
        dup2(pd[1], 1);
            execlp("gcc", "gcc", "au.c", "-o", "au", NULL);
            _exit(0);
        return 0;

    }
    wait(NULL);
    execl("./au", "au", NULL);
    close(pd[1]);
    dup2(pd[0], 0);
    double se = 0;
    for(int i = 0; i < n; i++) {
        scanf("%lf", &se);
        out = out + se * dx;
    }
    close(pd[0]);
    printf("%.10f\n", out);
    return 0;
}
