#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
int fp[2];
int i = 0;
char out = 0;
void hand1(int s)
{
    signal(SIGUSR1, hand1);
    signal(SIGUSR2, hand1);
    signal(SIGIO, hand1);
    int pid22;
    printf("/");
    read(fp[0], &pid22, sizeof(pid_t));
    write(fp[1], &pid11, sizeof(pid_t));
    write(fp[1], &pid22, sizeof(pid_t));
    if(s == SIGUSR2)
    {
        printf("1-\n");
        kill(pid22, SIGALRM);
        i++;
        out = out | 1u;
        if(i != 8)
        {
            out = out << 1;
        }
    }
    if(s == SIGUSR1)
    {
        printf("0\n");
        kill(pid22, SIGALRM);
        i++;
        out = out | 0u;
        if(i != 8)
        {
            out = out << 1;
        }
    }
    if(s == SIGIO)
    {
        read(fp[0], &pid11, sizeof(pid_t));
        kill(pid22, SIGALRM);
        while(i != 8)
        {
            i++;
            out = out << 1;
        }
        printf("%c", out);
        kill(pid11, SIGKILL);
        _exit(0);
    }
    if(i == 8)
    {
        printf("%c", out);
        out = 0;
        i = 0;
    }
    read(fp[0], &pid11, sizeof(pid_t));
}
void hand2(int s)
{
    signal(SIGALRM, hand2);
    kill(s)
}
int main(int argc, char *argv[])
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    signal(SIGUSR1, hand1);
    signal(SIGUSR2, hand1);
    signal(SIGALRM, hand2);
    signal(SIGIO, hand1);
    int pid1, pid2;
    int f = 0;
    pipe(fp);
    int fd = open(argv[1], O_RDONLY, 0666);
    if(!(pid1 = fork()))
    {
        close(fp[1]);
        while(1) pause();
        printf("*");
    }
    if(!(pid2 = fork()))
    {
        int pi = getpid();
        char x;
        int i = 0;
        close(fp[0]);
        write(fp[1], &pi, sizeof(pid_t));
        while((read(fd, &x, sizeof(x))) > 0)
        {
            for(i = 7; i >= 0 ; i--)
            {
                if(x & (1u << i))
                {
                    kill(pid1, SIGUSR2);

                }
                else
                {
                    kill(pid1, SIGUSR1);
                }
            }
        }
        kill(pid1, SIGIO);
        close(fp[1]);
        close(fd);
        _exit(0);
    }
    close(fd);
    close(fp[1]);
    close(fp[0]);
    wait(NULL);
    wait(NULL);
    return 0;
}
