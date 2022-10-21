#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
enum
{
    MOVE1 = 20,
    MOVE2 = 12,
    MOVE3 = 8
};
int
main(int argc, char **argv)
{
    char buf2[4] = {};
    int fd = creat (argv[1], 0600);
    unsigned int x = 0;
    while(scanf("%d", &x) == 1){
        buf2[0] = (x & 0xF00000) >> MOVE1;
        buf2[1] = (x & 0x0FF000) >> MOVE2;
        buf2[2] = (x & 0x000F00) >> MOVE3;
        buf2[3] = x  & 0x00000FF;
        write(fd, buf2, sizeof(buf2));

}
    close(fd);
    return 0;
}