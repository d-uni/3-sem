#include <stdio.h>
#include <stdlib.h>


double ***transpose(double ***arr)
{
    int i = 0, j = 0;
    while(arr[i][0] != NULL) {
        i++;
    }
    int high = i + 1;
    int *a = malloc(high * sizeof(int));
    j = 0;
    i = 0;
    int count = 0, maxlen = 0;
    for(i = 0; i < high; i++) {
        count = 0;
        for(j = 0; arr[i][j] != NULL; j++) {
            count++;
        }
        if(count > maxlen) {
            maxlen = count;
        }
        a[i] = count;
    }
    double ***out;
    out = (double ***) malloc((maxlen + 1) * sizeof(double **));
    for(j = 0; j < (maxlen + 1); j++) {
        out[j] = (double **) malloc(high * sizeof(double*));
    }
    for(i = 0; i < (maxlen + 1); i++) {
        for(j = 0; j < high; j++) {
            out[i][j] = (double *)malloc(sizeof(double));
            if(arr[j][i] != NULL && i < a[j]) {
                *out[i][j] = *arr[j][i];
            } else {
                out[i][j] = NULL;
            }
        }
    }
    out[maxlen][0] = NULL;
    int index = -1;
    for( j = 0; j < maxlen + 1; j++) {
        for( i = 0; i < high; i++) {
            if(out[j][i] != NULL) {
                index = i;
            }
        }
        for( i = 0; i < index && index != -1; i++) {
            if(out[j][i] == NULL) {
                out[j][i] = (double *)malloc(sizeof(double));
                *out[j][i] = 0;
            }
        }
        index = -1;
    }
    return out;
}
