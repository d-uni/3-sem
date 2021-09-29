#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
enum
{
    CONVERT_GAL = 493,
    CONVERT_SIK = 29
};
    int
    main
    (int argc, char **argv)
    {
    long long int max1 = LLONG_MIN, max2 = LLONG_MIN;
    int sum = 0;
    int fd;
    unsigned char buf[20] = {};
    for(int i = 1; i < argc; i++) {
    fd = open(argv[i],  O_RDONLY);
    while(read(fd, buf, sizeof(buf)) != 0) {
        sum = (unsigned)buf[16] << 24 | (unsigned)buf[17] << 16 | (unsigned)buf[18] << 8 | buf[19];
        if(sum > max2) {
            max1 = max2;
            max2 = sum;
        } else if((sum > max1) && (sum != max2)) {
            max1 = sum;
            }
        }
    close(fd);
    }
    if(max1 !=  LLONG_MIN ) {
        long long int res = max1;
        if(res < 0) {
        res = -res;
        printf("-%lldg%02llds%02lldk\n",res/CONVERT_GAL, res%CONVERT_GAL/CONVERT_SIK, res%CONVERT_SIK);
    } else {
        printf("%lldg%02llds%02lldk\n",res/ CONVERT_GAL, res%CONVERT_GAL/CONVERT_SIK, res%CONVERT_SIK);
        }
    }
    return 0;
}
