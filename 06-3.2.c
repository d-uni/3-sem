#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
enum
{
    SHIFT1 = 1,
    SHIFT2 = 2,
    SHIFT3 = 3
};
char *relativize_path(const char *path1, const char *path2) {
    int i = 0, j = 0, f1 = 0, f2 = 0, k = 0;

    if(path1[0] != '\0' && path1[0] == '/' && path1[SHIFT1] != '\0' && path1[SHIFT1] == '.'
        && path1[SHIFT2] != '\0' && path1[SHIFT2] == '.' && path1[SHIFT3] == '\0') {
        i = SHIFT2;
    }
    if(path1[0] != '\0' && path1[0] == '/' && path1[SHIFT1] != '\0' && path1[SHIFT1] == '.' && path1[SHIFT2] == '\0') {
        i = SHIFT1;
    }
    char *path11 = calloc((strlen(path1) + SHIFT1), sizeof(char));
    path11[0] = '/';
    path11[SHIFT1] = '\0';
    j = 1;
    i++;
    if(i == 1 && path1[i] != '\0' && path1[i] == '.' && path1[i + SHIFT1] != '\0' && path1[i + SHIFT1] == '/') {
        i = SHIFT2;
    }
    if(i == 1 && path1[i] != '\0' && path1[i] == '.' && path1[i + SHIFT1] != '\0'
        && path1[i + SHIFT1] == '.' && path1[i + SHIFT2] != '\0' && path1[i + SHIFT2] == '/') {
        i = SHIFT3;
    }
    while(path1[i] != '\0') {
        if(path1[i] == '/' && path1[i + SHIFT1] != '\0' && path1[i + SHIFT1] == '.'
            && path1[i + SHIFT2] == '\0') {
            i = i + SHIFT2;
            f1 = 1;
        }
        if(path1[i] == '/' && path1[i + SHIFT1] != '\0' && path1[i + SHIFT1] == '.'
            && path1[i + SHIFT2] != '\0' && path1[i + SHIFT2] == '/') {
            i = i + SHIFT2;
            f1 = 1;
        }
        if(path1[i] == '/' && path1[i + SHIFT1] != '\0' && path1[i + SHIFT1] == '.' && path1[i + SHIFT2] != '\0'
            && path1[i + SHIFT2] == '.' && path1[i + SHIFT3] == '\0') {
            i = i + SHIFT3;
            f2 = 1;
            while(path11[j] != '/' && j > SHIFT1) {
                path11[j] = '\0';
                j--;
            }
            path11[j] = '\0';
        }
        if(path1[i] == '/' && path1[i + SHIFT1] != '\0' && path1[i + SHIFT1] == '.' && path1[i + SHIFT2] != '\0'
            && path1[i + SHIFT2] == '.' && path1[i + SHIFT3] != '\0' && path1[i + SHIFT3] == '/') {
            i = i + SHIFT3;
            f2 = 1;
            while(path11[j] != '/' && j > SHIFT1) {
                path11[j] = '\0';
                j--;
            }
            path11[j] = '\0';
        }
        if(f1 == 0 && f2 == 0) {
            path11[j] = path1[i];
            j++;
            i++;
        }
        f1 = 0;
        f2 = 0;
    }
    i = 0;
    j = 0;
    f1 = 0;
    f2 = 0;
    if(path2[0] != '\0' && path2[0] == '/' && path2[SHIFT1] != '\0' && path2[SHIFT1] == '.'
        && path2[SHIFT2] != '\0' && path2[SHIFT2] == '.' && path2[SHIFT3] == '\0') {
            i = SHIFT2;
    }
    if(path2[0] != '\0' && path2[0] == '/' && path2[SHIFT1] != '\0' && path2[SHIFT1] == '.' && path2[SHIFT2] == '\0') {
        i = SHIFT1;
    }
    char *path22 = calloc((strlen(path2) + SHIFT1), sizeof(char));
    path22[0] = '/';
    path22[SHIFT1] = '\0';
    j = 1;
    i++;
    if(i == 1 && path2[i] != '\0' && path2[i] == '.' && path2[i + SHIFT1] != '\0' && path2[i + SHIFT1] == '/') {
        i = SHIFT2;
    }
    if(i == 1 && path2[i] != '\0' && path2[i] == '.' && path2[i + SHIFT1] != '\0'
        && path2[i + SHIFT1] == '.' && path2[i + SHIFT2] != '\0' && path2[i + SHIFT2] == '/') {
        i = SHIFT3;
    }
    while(path2[i] != '\0') {
        if(path2[i] == '/' && path2[i + SHIFT1] != '\0' && path2[i + SHIFT1] == '.'
            && path2[i + SHIFT2] == '\0') {
            i = i + SHIFT2;
            f1 = 1;
        }
        if(path2[i] == '/' && path2[i + SHIFT1] != '\0' && path2[i + SHIFT1] == '.'
            && path2[i + SHIFT2] != '\0' && path2[i + SHIFT2] == '/') {
            i = i + SHIFT2;
            f1 = 1;
        }
        if(path2[i] == '/' && path2[i + SHIFT1] != '\0' && path2[i + SHIFT1] == '.'
            && path2[i + SHIFT2] != '\0' && path2[i + SHIFT2] == '.' && path2[i + SHIFT3] == '\0') {
            i = i + SHIFT3;
            f2 = 1;
            while(path22[j] != '/' && j > SHIFT1) {
                path22[j] = '\0';
                j--;
            }
            path22[j] = '\0';
        }
        if(path2[i] == '/' && path2[i + SHIFT1] != '\0' && path2[i + SHIFT1] == '.'
            && path2[i + SHIFT2] != '\0' && path2[i + SHIFT2] == '.' && path2[i + SHIFT3] != '\0'
                && path2[i + SHIFT3] == '/') {
            i = i + SHIFT3;
            f2 = 1;
            while(path22[j] != '/' && j > SHIFT1) {
                path22[j] = '\0';
                j--;
            }
            path22[j] = '\0';
        }
        if(f1 == 0 && f2 == 0) {
            path22[j] = path2[i];
            j++;
            i++;
        }
        f1 = 0;
        f2 = 0;
    }
    char *out = (char *)malloc(PATH_MAX*sizeof(char));
    for(i = 0; i < PATH_MAX; i++) {
        out[i] = '\0';
    }
    int size = 0;
    i = strlen(path11);
    while(path11[i] != '/') {
        i--;
    }
    i++;
    j = 0;
    int p = 0;
    while(path22[j] == path11[j] && (j < i)) {
        j++;
    }
    k = 0;
    if(path11[j] != '\0') {
        while(path11[j + k + SHIFT1] != '\0') {
            if(path11[j + k + SHIFT1] == '/') {
                size++;
            }
            k++;
        }
    }
    int x = 0;
    for(p = 0; p < size; p++) {
        out[x + SHIFT2] = '/';
        out[x + SHIFT1] = '.';
        out[x] = '.';
        x = x + SHIFT3;
    }
    if(path22[j] == '/') {
        j++;
    }
    while(path22[j] != '\0') {
        out[x] = path22[j];
        x++;
        j++;
    }

    if(x > 0 && out[x - SHIFT1] == '/') {
        out[x - SHIFT1] = '\0';
    }
    if(out[0] == '\0') {
        out[0] = '.';
    }
    free(path11);
    free(path22);
    return out;
}
