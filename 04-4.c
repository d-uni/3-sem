#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void inOder(int fd, int offset)
{
    if(offset != 0 ) {
        if(offset == -1){
            offset = 0;
        }
        lseek(fd, offset*3*sizeof(int) + 2 * sizeof(int), SEEK_SET);
        int right;
        char buf[4];
        ssize_t count;
        int tmp = 0;
        while ((count = read(fd, buf + tmp , 4 - tmp)) > 0) {
            tmp += count;
            if(tmp == 4) {
                break;
            }
        }
        right = *((int*)buf);
        inOder(fd, right);
        lseek(fd, offset*3*sizeof(int), SEEK_SET);
        int key;
        tmp = 0;
        while ((count = read(fd, buf + tmp , 4 - tmp)) > 0) {
            tmp += count;
            if(tmp == 4) {
                break;
            }
        }
        key = *((int*)buf);
        printf("%d\n", key);
        lseek(fd, offset*3*sizeof(int) + sizeof(int), SEEK_SET);
        int left;
        tmp = 0;
        while ((count = read(fd, buf + tmp , 4 - tmp)) > 0) {
            tmp += count;
            if(tmp == 4) {
                break;
            }
        }
        left = *((int*)buf);
        inOder(fd, left);
        }
}

int
main(int argv, char **argc)
{
    int fd = open(argc[1], O_RDONLY);
    int offset = -1;
    char buf1[1];
    if(read(fd, buf1, sizeof(buf1)) != 0){
        inOder(fd, offset);
    }
    close(fd);
    return 0;
}