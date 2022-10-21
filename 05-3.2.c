#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
enum
{
    BASIS = 10,
    SHIFT = 1
};
int
main(void)
{
    uint32_t n = 0, s = 0, output1 = 0, uint_max = 1, mask = 0, i = 0;
    int32_t output2 = 0, w = 0;
    scanf("%"PRIu32"%"PRIu32"%"PRIu32"", &n, &s, &w);
    n -= SHIFT;
    mask = SHIFT << n;
    for (i = 1; i <= n; ++i) {
        uint_max = uint_max << SHIFT;
        uint_max += SHIFT;
    }
    while (1) {
        printf("|");
        printf("%*"PRIo32"|", (int) w, output1);
        printf("%*"PRIu32"|", (int) w, output1);
        output2 = output1 & (uint_max >> SHIFT);
        if (output1 & mask) {
            output2 = -output2;
            printf("%*"PRId32"|\n", (int) w, output2);
        } else {
            printf("%*"PRId32"|\n", (int) w, output2);
        }
        if(output1 <= uint_max - s) {
            output1 += s;
        } else {
            break;
        }
    }
    return 0;
}
