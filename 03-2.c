#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char **argv)
{
    unsigned short c = 0;

    int fd = open(argv[1], O_CREAT | O_WRONLY, 0600);
    while(scanf("%hu", &c) == 1) {
    char t[2];
    t[0] = c >> 8;
    t[1] = c;
    write(fd, t, sizeof(c));
    }
    close(fd);
    return 0;
}
