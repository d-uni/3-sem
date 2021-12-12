#include <stdio.h>
#include <stdlib.h>


double ***transpose(double ***arr)
{
    int i = 0, j = 0;
    while(arr[i][0] != NULL)
    {
        i++;
    }
    int high = i + 1;
    int *a = calloc(high, sizeof(int));
    j = 0;
    i = 0;
    int count = 0, maxlen = 0;
    for(i = 0; i < high; i++)
    {
        count = 0;
        for(j = 0; arr[i][j] != NULL; j++)
        {
            count++;
        }
        if(count > maxlen)
        {
            maxlen = count;
        }
        a[i] = count;
    }
    double ***out;
    out = (double ***) calloc((maxlen + 1), sizeof(double **));
    for(j = 0; j < (maxlen + 1); j++)
    {
        out[j] = (double **) calloc(high, sizeof(double*));
    }
    for(i = 0; i < (maxlen + 1); i++)
    {
        for(j = 0; j < high; j++)
        {
            out[i][j] = (double *) calloc(1, sizeof(double));
            if(i < a[j] && arr[j][i] != NULL)
            {
                *out[i][j] = *arr[j][i];
            }
            else
            {
                out[i][j] = NULL;
            }
        }
    }
    out[maxlen][0] = NULL;
    int index = -1;
    for( j = 0; j < maxlen + 1; j++)
    {
        for( i = 0; i < high; i++)
        {
            if(out[j][i] != NULL)
            {
                index = i;
            }
        }
        for( i = 0; i < index && index != -1; i++)
        {
            if(out[j][i] == NULL)
            {
                out[j][i] = (double *)calloc(1, sizeof(double));
                *out[j][i] = 0;
            }
        }
        index = -1;
    }
    free(a);
    return out;
}
int main()
{
    int n = 4, m = 5;//n и m – количество строк и столбцов матрицы
    double ***matr; //указатель для массива указателей
    double x[10];
    for(int i = 0; i<10; i++)
    {
        x[i] = i;
    }
    matr = (double ***) malloc(n*sizeof(double **));
    for (int i=0; i < n; i++)
    {
        matr[i] = (double **) malloc(m*sizeof(double*));
    }
    for(int j = 0; j<n; j++)
    {
        for(int i = 0; i < m ; i++)
        {
            matr[j][i] = (double *)malloc(sizeof(double));
        }
    }
    matr[0][0] = &x[1];
    matr[0][1] = &x[2];
    matr[0][2] = &x[3];
    matr[0][3] = NULL;
    matr[0][4] = NULL;
    matr[1][0] = &x[4];
    matr[1][1] = &x[5];
    matr[1][2] = &x[6];
    matr[1][3] = &x[7];
    matr[1][4] = NULL;
    matr[2][0] = &x[8];
    matr[2][1] = NULL;
    matr[2][2] = NULL;
    matr[2][3] = NULL;
    matr[2][4] = NULL;
    matr[3][0] = NULL;
    matr[3][1] = NULL;
    matr[3][2] = NULL;
    matr[3][3] = NULL;
    matr[3][4] = NULL;
    for(int j = 0; j<n; j++)
    {
        matr[j][m-1] = NULL;
    }
    for(int i = 0; i < m ; i++)
    {
        matr[n-1][i] = NULL;
    }
    for(int j = 0; j<n; j++)
    {
        for(int i = 0; (i < m)  && (matr[j][i] != NULL); i++)
        {
            printf("*%lf ",*matr[j][i]);
        }
        printf("*\n");
    }
    double ***out = transpose(matr);
    for(int j = 0; out[j][0]!=NULL; j++)
    {
        for(int i = 0; out[j][i]!=NULL; i++)
        {
            printf("*%lf ",*out[j][i]);
        }
        printf("*\n");
    }

    //выделение динамической памяти для массива значений
    printf("Hello world!\n");
    return 0;
    }
