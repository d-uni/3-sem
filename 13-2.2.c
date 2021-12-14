/* Напишите функцию calc_max_size с прототипом:

int64_t calc_max_size(int64_t block_size, int64_t block_num_size, int64_t inode_direct_block_count);

Параметр block_size — это размер блока диска в байтах (положительное число). Параметр block_num_size — размер числа для хранения номера блока диска в байтах (положительное число, не больше чем размер блока диска). Параметр inode_direct_block_count — число номеров блоков, хранящихся непосредственно в индексном дескрипторе.

Предполагая принцип хранения занятых файлом блоков диска, реализованный в файловых системах Unix (то есть с ссылочными блоками 1-, 2- и 3- уровня косвенности), функция должна вычислить теоретический максимальный поддерживаемый размер файла в байтах. Если размер не представим 64-битным знаковым целым числом, функция должна возвращать значение -1. Накладными расходами на организацию самой файловой системы пренебрегайте.

Напишите программу: программе на стандартный поток ввода задаются три числа: block_size, block_num_size, inode_direct_block_count. Программа на стандартный поток вывода выводит теоретический максимальный поддерживаемый размер файла для заданных входных данных. Затем программа находит такое значение block_num_size, при котором теоретический максимальный поддерживаемый размер файла был бы максимальным и выводит найденное значение и соответствующий теоретический максимальный поддерживаемый размер файла.

Максимальный возможный теоретический максимальный поддерживаемый размер файла в терминах возвращаемого функцией calc_max_size значения равен 263-1, то есть поддерживается файл размера, представимого 64-битным знаковым числом. Если при нескольких размерах block_num_size достигается максимум, выведите минимальное.
Examples
Input

512 3 10

Output

2530344960
3 2530344960 */

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
    for(int64_t i = 1; i <= x1; i ++) {
        a = calc_max_size(x1, i, x3);
        if(a == -1) {
            printf("%lld -1\n", i);
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
