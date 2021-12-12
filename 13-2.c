#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int64_t overflow_mul(int64_t x1, int64_t x2)
{
    if(x1 != 0) {
        if(LLONG_MAX / x1  < x2) {
            return -1;
        }
    }
    return x1 * x2;
}
int64_t overflow_add(int64_t x1, int64_t x2)
{
    if(LLONG_MAX - x1  < x2) {
        return -1;
    } else {
        return x1 + x2;
    }
}
int64_t powov(int64_t x)
{
    int64_t result = 1;
    for(int64_t i = 1; i <= x; i++)
    {
        result = overflow_mul(result, 2);
        if(result == -1)
        {
            return -1;
        }
    }
    return result;
}

int64_t calc_max_size(int64_t block_size, int64_t block_num_size, int64_t inode_direct_block_count)
{
    int f1 = 0, f2 = 0;
    int64_t out1 = overflow_mul(8, block_num_size);
    if(out1 == -1) {
        f1 = 1;
    } else {
        out1 = powov(out1);
        if(out1 == -1) {
            f1 = 1;
        } else {
            out1 = overflow_mul(out1, block_size);
            if(out1 == -1) {
                f1 = 1;
            }
        }
    }
    int64_t sum3 = -1;
    int64_t nod = block_size / block_num_size;
    int64_t sum1 = overflow_mul(nod,nod);
    if(sum1 == -1) {
        f2 = 1;
    } else {
        int64_t sum2 = overflow_mul(sum1,nod);
        if(sum2 == -1) {
            f2 = 1;
        } else {
            sum3 = overflow_add(nod, inode_direct_block_count);
            if(sum3 == -1) {
                f2 = 1;
            } else {
                sum3 = overflow_add(sum3, sum1);
                if(sum3 == -1) {
                    f2 = 1;
                } else {
                    sum3 = overflow_add(sum3, sum2);
                    if(sum3 == -1) {
                        f2  = 1;
                    } else {
                        sum3 = overflow_mul(sum3, block_size);
                        if(sum3 == -1) {
                            f2 = 1;
                        }
                    }
                }
            }
        }
    }
    if(f2 == 1 && f1 == 1) {
        return -1;
    } else if(f1 == 1) {
        return sum3;
    } else if(f2 == 1) {
        return out1;
    } else if (sum3 < out1) {
        return sum3;
    } else {
        return out1;
    }

}
int
main()
{
    int64_t x1, x2, x3;
    int64_t max = -1, a = -1, b = 0;
    scanf("%lld %lld %lld", &x1, &x2, &x3);
    int64_t out = calc_max_size(x1, x2, x3);
    printf("%lld\n", out);
    for(int i = 1; i <= x1; i ++) {
        a = calc_max_size(x1, i, x3);
        if(a == -1) {
            printf("%lld -1\n", b);
            return 0;
        }
        if (a > max) {
            max = a;
            b = i;
        }
    }
    printf("%lld %lld\n", b, max);
    return 0;

}
