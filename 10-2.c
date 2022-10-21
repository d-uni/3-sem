#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
int mysys(const char *str)
{
    pid_t pid;
    int status = -1;
    if((pid = fork()) < 0) {
        return -1;
    } else if(!pid) {
        execlp("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    }
    waitpid(pid, &status, 0);
    if(WIFSIGNALED(status) != 0) {
        return 128 + WTERMSIG(status);
    } else {
        return WEXITSTATUS(status);
    }
    return -1;
}
