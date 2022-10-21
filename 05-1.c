#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
enum
{
    MOV = 1024
};

int
main(int argv, char **argc)
{
    struct stat stbuf;
    long long int sum = 0;
    for(int i = 1; i < argv; i++) {
        if(lstat(argc[i], &stbuf) != -1) {
        if( (access(argc[i], F_OK) == 0)
            & (stbuf.st_size % MOV == 0)
                & ((stbuf.st_mode & S_IFMT) == S_IFREG)
                    & ((stbuf.st_mode & S_IFMT) != S_IFLNK)
                        & (stbuf.st_nlink == 1)) {
                            sum = sum + stbuf.st_size;
                            }
        }
    }
    printf("%lld\n", sum);
    return 0;
}