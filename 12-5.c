#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
volatile sig_atomic_t f = 0, countint = 0;
void handler(int sig) {
    signal(SIGINT, handler);
    signal(SIGTERM, handler);
    if(sig == SIGINT) {
        if(countint == 3) {
            _exit(0);
        }
        f = 1;
        countint++;
    } else if(sig == SIGTERM) {
        _exit(0);
    }
}
int check(int x)
{
    if(x == 1) {
        return 0;
    }
    for(int i = 2; i * i <= x; i ++) {
        if(x % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main()
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    signal(SIGINT, handler);
    signal(SIGTERM, handler);
    int low, high;
    scanf("%d", &low);
    scanf("%d", &high);
    printf("%d\n", getpid());
    fflush(stdout);
    if(low < 2) {
        low = 2;
    }
    int c;
    for(c = low; c < high; c++) {
        if(check(c)) {
            if(f == 1) {
                printf("%d\n", c);
                f = 0;
            }
        }

    }
    printf("-1\n");
    fflush(stdout);
    _exit(0);
}
