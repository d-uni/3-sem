#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
enum
{
    SIZE_INT = 11,
    SIZE_CH = 1
};
int form(void)
{
    pid_t pid;
    int st;
    pid = fork();
    if (pid == -1) {
        return 1;
    }
    if (pid == 0) {
        setbuf(stdin, NULL);
        setbuf(stdout, NULL);
        int x;
        if (scanf("%d", &x) <= 0) {
            _exit(0);
        } else {
            int flg = form();
            if(flg == 1) {
                _exit(1);
            } else {
                printf("%d\n", x);
                _exit(0);
            }
        }
    } else if(pid > 0) {
        waitpid(pid, &st, 0);
        if (WIFEXITED(st) != 0 && WEXITSTATUS(st) == 0) {
            return 0;
        } else {
            return 1;
        }
    }
    return 0;
}
int
main(void)
{
    setbuf(stdin, NULL);
    if(form() == 1) {
        setbuf(stdout, NULL);
        printf("-1\n");
    }
    return 0;
}
