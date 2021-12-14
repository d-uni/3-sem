/* В параметрах командной строки задаются параметры memory_size, cache_size, block_size, определяющие размер ОЗУ, размер кеш-памяти и размер блока кеш-памяти. Размер блока - один из 16, 32, 64 байта. Размер памяти и размер кеша кратны размеру блока.

В кеше прямого отображения (direct mapping) блок ОЗУ может размещаться в единственном блоке кеша, номер которого определяется по формуле cache_block_num = memory_block_num % block_count, где block_count - число блоков кеша.

На стандартный поток ввода подается трасса выполнения программы. Трасса задается в формате:

R (D|I) ADDR SIZE VALUE

Где R означает чтение, W – запись, D – работу с данными, I – работу с инструкциями, ADDR – 32-битный адрес, задаваемый в 16-ричном виде, SIZE – размер операции (1, 2, 4 байта), VALUE – считываемое значение — число в десятичной системе счисления со знаком соответствующего размера. Например.

RD 00000000 1 0
RD 00000001 1 0
RD 00000002 1 0

На стандартный поток вывода напечатайте число промахов в кеше, причиной которых служит стратегия прямого отображения, то есть число случаев, когда при чтении из памяти блок кеша, в который должен быть загружен блок памяти, уже занят другим блоком памяти. */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int cache_size = atoi(argv[2]);
    int block_size = atoi(argv[3]);
    int block_count = cache_size / block_size;
    int *cach = malloc(block_count * sizeof(int));
    for (int i = 0; i < block_count; i ++) {
        cach[i] = -1;
    }
    int miss = 0;
    char rwdi[2];
    int addr;
    int size;
    int value;
    while((scanf("%s %x %d %d", rwdi, &addr, &size, &value) > 0)) {
        int b_num = addr / block_size;
        if(rwdi[0] == 'R') {
            if( cach[b_num % block_count] != b_num && cach[b_num % block_count] != -1) {
                miss++;
            }
            cach[b_num % block_count] = b_num;
        } else if(rwdi[0] == 'W') {
            cach[b_num % block_count] = b_num;
        }
    }
    printf("%d\n", miss);
    return 0;
}
