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
int form(int n, int count)
{
    if(n + 1 == count) {
        return 0;
    }
    pid_t pid;
    int st;
    pid = fork();
    if (pid == -1) {
        return 1;
    }
    if (pid == 0) {
        setbuf(stdin, NULL);
        setbuf(stdout, NULL);
        printf("%d", count);
        if(count != n) {
            printf(" ");
        }
        count = count + 1;
        int flg = form(n, count);
        if(flg == 1) {
            _exit(1);
        } else {
            _exit(0);
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
    int n;
    scanf("%d", &n);
    form(n, 1);
    printf("\n");
    return 0;
}



/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int
main(void)
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        wait(NULL);
        if (fork() == 0) {
            int number = i + 1;
            printf("%d", number);
            if (i == n - 1) {
                printf("\n");
            } else {
                printf(" ");
            }
            return 0;
        }
    }
    return 0;
}*/
