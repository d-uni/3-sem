/* "Рваная" матрица вещественных чисел представлена указателем типа double *** следующим образом: матрица размещается по строкам, каждая элемент массива строк - это указатель на массив указателей на double (то есть каждая строка массива имеет тип double **). Каждый элемент строки - указатель на double. Массив строк завершается нулевым указателем, каждая строка завершается нулевым указателем. Строки могут иметь разную длину.

Например, рассмотрим матрицу arr:

1 2 3
4 5 6 7
8

Она представляется в виде массива из трех указателей, за которым следует элемент NULL.

[0] -> {1}, {2}, {3}, NULL
[1] -> {4}, {5}, {6}, {7}, NULL
[2] -> {8}, NULL
[3] -> NULL

То есть элемент arr[0] - это указатель на массив из 3 указателей, за которыми идет нулевой указатель. Элемент arr[0][1] - это указатель на значение 2.0 типа double. Нулевой указатель не может встретиться в середине массива значений.

Напишите функцию, которая транспонирует массив массивов. Функция должна вернуть новый транспонированный массив. Сами числа double должны быть скопированы.

double ***transpose(double ***arr);

При этом, если в результате транспонирования в середине строки появляются нулевые указатели, они должны заменяться на указатель на вещественное значение 0 (каждый раз новый).

Например, матрица:

 1 2 3
 4 5 6 7
8

транспонируется в

1 4 8
2 5
3 6
0 7

Матрица

1
2 3
4 5 6

транспонируется в

1 2 4
0 3 5
0 0 6*/
#include <stdio.h>
#include <stdlib.h>
double ***transpose(double ***arr)
{
    int i = 0, j = 0;
    while(arr[i] != NULL) {
        i++;
    }
    int high = i + 1;
    int *a = calloc(high, sizeof(int));
    j = 0;
    i = 0;
    int count = 0, maxlen = 0;
    for(i = 0; i < high; i++) {
        count = 0;
        for(j = 0;arr[i] != NULL && arr[i][j] != NULL; j++) {
            count++;
        }
        if(count > maxlen) {
            maxlen = count;
        }
        a[i] = count;
    }
    double ***out;
    out = (double ***) calloc((maxlen + 1), sizeof(double **));
    for(j = 0; j < (maxlen + 1); j++) {
        out[j] = (double **) calloc(high, sizeof(double*));
    }
    for(i = 0; i < (maxlen + 1); i++) {
        for(j = 0; j < high; j++) {
            out[i][j] = (double *) calloc(1, sizeof(double));
            if(i < a[j] && arr[j] != NULL && arr[j][i] != NULL) {
                *out[i][j] = *arr[j][i];
            }
            else {
                free(out[i][j]);
                out[i][j] = NULL;
            }
        }
    }
    int index = -1;
    for( j = 0; j < maxlen + 1; j++) {
        for( i = 0; i < high; i++) {
            if(out[j][i] != NULL)
            {
                index = i;
            }
        }
        if(index != -1) {
            for( i = 0; i < index; i++)
            {
                if(out[j][i] == NULL) {
                    out[j][i] = (double *)calloc(1, sizeof(double));
                    *out[j][i] = 0;
                }
            }
        }
        index = -1;
    }
    for(i = 0; i < high; i++) {
        free(out[maxlen][i]);
    }
    free(out[maxlen]);
    out[maxlen] = NULL;
    free(a);
    return out;
}
