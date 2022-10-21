#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
    int n = 0, i = 0;
    unsigned long long int result[6], real_sum = 0, part_res[6], delta = 0;
    for(i = 0; i < 6; i++) {
        result[i] = 0;}
    unsigned short count = 0, sum = 0, voice = 0;
    int fd = open(argv[1], O_RDONLY );
    while((n = read(fd, &count, sizeof(count)))!=0){
        read(fd, &sum, sizeof(sum));
        if(real_sum != sum) {
            delta = sum - real_sum ;
            for(i = 1; i < 5; i++) {
                result[i + 1] += part_res[i];
                result[i] -=  part_res[i];
                delta -= part_res[i];
                }
            result[1] = result[1] + delta;
            result[0] = result[0] - delta;
            }
        for(i = 0; i < 6; i++) {
            part_res[i] = 0;
            }
        real_sum = 0;
        for(i = 0; i < count; i++) {
            read(fd, &voice, sizeof(voice));
            result[voice - 1] ++;
            part_res[voice - 1] ++;
            real_sum = real_sum + voice;
            }
    }
    for(i = 0; i < 6; i++) {
        printf("%lld\n", result[i]);
        }
    close(fd);
    return 0;
}