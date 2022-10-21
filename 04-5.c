#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
int
main(int argv, char **argc)
{
    long long int min = LLONG_MAX;
    int f = 0;
    long long num;
    int n;
    off_t offset = 0;
    int fd = open(argc[1], O_RDWR);
    if(read(fd, &num, sizeof(num)) != 0){
    lseek(fd, 0, SEEK_SET);
    while((n  = read(fd, &num, sizeof(num))) > 0) {
        if(num < min) {
            offset = lseek(fd, 0, SEEK_CUR);
            min = num;
        } else if (num == LLONG_MAX && f == 0 && min == LLONG_MAX) {
            f = 1;
            offset = lseek(fd, 0, SEEK_CUR);
            min = num;
        }
    }
    lseek(fd, 0, SEEK_SET);
    offset -= sizeof(num);
    lseek(fd, offset, SEEK_SET);
    read(fd, &num, sizeof(num));
    if(num != LLONG_MIN) {
        num = ~num +1;}
    lseek(fd, offset, SEEK_SET);
    write(fd, &num, sizeof(num));
    }
    close(fd);
    return 0;
}