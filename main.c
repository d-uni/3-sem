#include <stdio.h>
#include <stdlib.h>
#include <math.h>
enum
{
    TO_FRACTION = 100,
    TO_ROUND = 10000,
    PERCENT_STARTS = 2
};
    int
    main(int argc, char **argv)
    {
    double ex_rate;
    double percent;
    ex_rate = atof(argv[1]);
    for (int i = PERCENT_STARTS; i < argc; i++) {
        percent = atof(argv[i]);
        ex_rate = ex_rate + percent / TO_FRACTION * ex_rate;
        ex_rate *= TO_ROUND;
        ex_rate = round(ex_rate) / TO_ROUND;
    }
    printf("%.4f\n", ex_rate);
    return 0;
    }
