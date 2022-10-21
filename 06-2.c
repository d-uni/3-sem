#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
enum
{
    RES = 1000000
};
int
main(int argv, char *argc[])
{
    struct timeval *restrict t0 = (struct timeval *restrict)malloc(sizeof(struct timeval));
    sscanf(argc[1],"%ld", &(t0 -> tv_sec));
    sscanf(argc[2],"%ld", &(t0 -> tv_usec));
    double lamd = atof(argc[3]);
    int k = atoi(argc[4]);
    unsigned int s = 0;
    sscanf(argc[5],"%ud", &s);
    double u = 0, delta = 0;
    srand(s);
    int i;
    for(i = 0; i < k; ++i) {
        u = rand();
        u = u / RAND_MAX;
        delta = -log(u)/lamd;
        t0 -> tv_sec += (time_t)floor(delta + t0 -> tv_usec) / RES;
        t0 -> tv_usec = (t0 -> tv_usec + (long)floor(delta)) % RES;
        printf("%ld %ld\n", t0 -> tv_sec, t0 -> tv_usec);
    }
    return 0;
}
