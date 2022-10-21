#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (fd < 0) {
        fprintf(stderr, "open_error\n");
        return 1;
    }
    int rows = atoi(argv[2]);
    int cols = atoi(argv[3]);
    int value = rows * cols;
    size_t size = rows * cols * sizeof(value);
    ftruncate(fd, size);
    void *vptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (vptr == MAP_FAILED) {
        return 1;
    }
    int *wr = vptr;
    int **a = (int **) malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; i++ ) {
        a[i] = (int *) malloc(sizeof(int) * cols);
    }
    int i, j, m = 1;
    for (i = 0; (i < rows/2 + rows % 2) && m <= value; i++) {
        for (j = i; j < (cols - i) && m <= value; j++) {
            a[i][j] = m;
            m++;
        }
        for (j = 1; j < (rows - i - i) && m <= value; j++) {
            a[(j + i)][(cols - i) - 1] = m;
            m++;
        }
        for (j = (cols - 2) - i; j >= i && m <= value; j--) {
            a[(rows - i) - 1][j] = m;
            m++;
        }
        for (j = ((rows - i) - 2); j > i && m <= value; j--) {
            a[j][i] = m;
            m++;
        }
    }
    int s = 0;
    for (i = 0; i < rows; i++) {
        for(j = 0; j < cols - 1; j++) {
            wr[s] = a[i][j];
            s++;
        }
        wr[s] = a[i][cols-1];
        s++;
    }

    munmap(vptr, size);
    close(fd);
    for (i = 0; i < rows; i++ ) {
        free(a[i]);
    }
    free(a);
    return 0;
}
