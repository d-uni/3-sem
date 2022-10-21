#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
enum
{
    DAY_SEC = 2,
    DAY_FOUR = 4,
    THURS = 4,
    SHIFT = 1900,
    CHECK = 3,
    HOUR = 12
};
int
main(void)
{
    int year = 0;
    scanf("%d", &year);
    struct tm time;
    int f = 0;
    int prev = 1;
    memset(&time, 0, sizeof(time));
    time.tm_isdst = -1;
    time.tm_year =  year - SHIFT;
    time.tm_hour = HOUR;
    time.tm_mon = 0;
    while(time.tm_year == year - SHIFT) {
        time.tm_mday ++;
        mktime(&time);
        time.tm_isdst = -1;
        if(time.tm_mon != prev) {
            f = 0;
        }
        if(time.tm_wday == THURS) {
            f++;
        }
        if(time.tm_wday == THURS && (f == DAY_SEC || f == DAY_FOUR) && time.tm_mday % CHECK != 0) {
            printf("%d %d\n", time.tm_mon + 1, time.tm_mday);
        }
        prev = time.tm_mon;
    }
    return 0;
}
