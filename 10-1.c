#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
    pid_t pid;
    int status = -1;
    if((pid = fork()) < 0) {
        return -1;
    }
    else if(!pid) {
        int fd_in = open(argv[2],  O_RDONLY, 0);
        if(fd_in == -1) {
            _exit(42);
        }
        int x = dup2(fd_in, 0);
        if(x == -1) {
            _exit(42);
        }
        int fd_out = open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0660);
        if(fd_out == -1) {
            _exit(42);
        }
        x = dup2(fd_out, 1);
        if(x == -1) {
            _exit(42);
        }
        int fd_err = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0660);
        if(fd_err == -1) {
            _exit(42);
        }
        x = dup2(fd_err, 2);
        if(x == -1) {
            _exit(42);
        }
        execlp(argv[1],argv[1], NULL);
        x = close(fd_in);
        if(x == -1) {
            _exit(42);
        }
        x = close(fd_out);
        if(x == -1) {
            _exit(42);
        }
        x = close(fd_err);
        if(x == -1) {
            _exit(42);
        }
        _exit(42);
    }
    wait(&status);
    printf("%d\n", status);
    return 0;
}
