#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    pid_t pid1, pid2, pid3;
    int status1 = -1, status2 = -1, status3 = -1;
    if((pid1 = fork()) < 0) {
        if((pid2 = fork()) < 0) {
                return 1;
            } else if(!pid2) {
                execlp(argv[2], argv[2], NULL);
                _exit(2);
            }
            waitpid(pid2, &status2, 0);
            if(WIFEXITED(status2) != 0 && WEXITSTATUS(status2) == 0) {
                if((pid3 = fork()) < 0) {
                    return 1;
                } else if(!pid3) {
                    execlp(argv[3], argv[3], NULL);
                    _exit(3);
                }
                waitpid(pid3, &status3, 0);
                if(WIFEXITED(status3) != 0 && WEXITSTATUS(status3) == 0) {
                    return 0;
                } else {
                    return 1;
                }
            } else {
                return 1;
            }
    } else if(!pid1) {
        execlp(argv[1], argv[1], NULL);
        _exit(1);
    }
    waitpid(pid1, &status1, 0);
    if(WIFEXITED(status1) != 0 && WEXITSTATUS(status1) == 0) {
        if((pid3 = fork()) < 0) {
            return 1;
        } else if(!pid3) {
            execlp(argv[3], argv[3], NULL);
            _exit(3);
        }
        waitpid(pid3, &status3, 0);
        if(WIFEXITED(status3) != 0 && WEXITSTATUS(status3) == 0) {
            return 0;
        } else {
            return 1;
        }
    } else {
        if((pid2 = fork()) < 0) {
                return 1;
            } else if(!pid2) {
                execlp(argv[2], argv[2], NULL);
                _exit(2);
            }
            waitpid(pid2, &status2, 0);
            if(WIFEXITED(status2) != 0 && WEXITSTATUS(status2) == 0) {
                if((pid3 = fork()) < 0) {
                    return 1;
                } else if(!pid3) {
                    execlp(argv[3], argv[3], NULL);
                    _exit(3);
                }
                waitpid(pid3, &status3, 0);
                if(WIFEXITED(status3) != 0 && WEXITSTATUS(status3) == 0) {
                    return 0;
                } else {
                    return 1;
                }

            } else {
                return 1;
            }
    }
    return 0;
}
