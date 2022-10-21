#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
typedef struct DIR
{
    int fd;
    struct dirent d;
} Dir;
int sort(const void *a, const void *b) {
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}
int
run(char *s)
{
    DIR *d = opendir(s);
    if(!d) {
        return 0;
    }
    int j = 0;
    struct dirent *dd;
    char **point = calloc(1, sizeof(char *));
    int i = 0;
    while ((dd = readdir(d))) {
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) continue;
        if((strlen(s) + strlen(dd -> d_name)) > PATH_MAX) continue;
        char *path = calloc(PATH_MAX, sizeof(*path));
        snprintf(path, PATH_MAX, "%s/%s", s, dd -> d_name);
        struct stat stb;
        if (lstat(path, &stb) < 0) continue;
        if((stb.st_mode & S_IFMT) == S_IFDIR) {
            point = realloc(point, i * sizeof(char *) + sizeof(char *));
            point[i] = calloc(sizeof(dd -> d_name), sizeof(char));
            memcpy(point[i], dd -> d_name, sizeof(dd -> d_name));
            i++;
        } else {
            free(path);
        }
    }
    closedir(d);
    qsort(point, i, sizeof(char *), sort);
    char *add = s + strlen(s);
    for(j = 0; j < i; j++) {
        snprintf(add, PATH_MAX, "/%s", point[j]);
        DIR *dpp = opendir(s);
        if (dpp) {
            closedir(dpp);
            printf("cd %s\n", point[j]);
            run(s);
            printf("cd ..\n");
        }
        free(point[j]);
    }
    free(point);
    return 0;
}
int
main(int argc, char *argv[])
{
    run(argv[1]);
    return 0;
}