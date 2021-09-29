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
    int sum = 0;                     ///unsigned int sum = 0;  и   int sumi = 0;
    int fd, n;
    unsigned char buf[20] = {};
    for(int i = 1; i < argc; i++) {
    fd = open(argv[i],  O_RDONLY);
    while((n = read(fd, buf, sizeof(buf))) != 0) {
        sum = buf[16] << 24 | buf[17] << 16 | buf[18] << 8 | buf[19];
                                                           /// sumi = (int)sum;
        if(sum > max2) {                                   ///if(sumi > max2) {
            max1 = max2;                                   ///max1 = max2;
            max2 = sum;                                    /// max2 = sumi;
        } else if((sum > max1) && (sum != max2)) {         /// } else if((sumi > max1) && (sumi != max2)) {
            max1 = sum;                                    ///  max1 = sumi;}
            }
        }
    close(fd);
    }
    if(max1 !=  LLONG_MIN ) {
        int res = (int)max1;
        if(res < 0) {
        res = -res; /// res = ~res+1
        printf("-%dg%02ds%02dk\n",res/CONVERT_GAL, res%CONVERT_GAL/CONVERT_SIK, res % CONVERT_SIK);
    } else {
        printf("%dg%02ds%02dk\n",res/ CONVERT_GAL, res% CONVERT_GAL / CONVERT_SIK, res % CONVERT_SIK);
        }
    }
    return 0;
}
