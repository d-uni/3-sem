#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

int
main
(int argc, char **argv)
{
    unsigned short input = 0;
    unsigned int min = USHRT_MAX + 1;
    int fd = open(argv[1], O_RDWR);
    unsigned char buf[2] = {};
    int n;
    while ((n = read(fd, buf, sizeof(buf))) != 0) {
        input = (unsigned)buf[0] << 8 | (unsigned)buf[1];
        if (input < min && (input % 2 == 0)) {
            min = input;
        }
    }
    if (min != USHRT_MAX + 1) {
        printf("%u\n", min);
    }
    close(fd);
    return 0;
}