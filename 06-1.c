#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
int
main(int argc, char *argv[])
{
    DIR *d = opendir(argv[1]);
    if(!d) {
        exit(1);
    }
    long long int count = 0;
    struct dirent *dd;
    while((dd = readdir(d))) {
        if(!strcmp(dd -> d_name, ".") || !strcmp(dd -> d_name, "..")) {
            continue;
        }
        char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s/%s", argv[1], dd -> d_name);
        struct stat stb;
        if(stat(path, &stb) < 0) {
            continue;
        }
        if(! S_ISREG(stb.st_mode)) {
            continue;
        }
        if(access(path, X_OK) == -1) {
            continue;
        }
        if(! (((dd -> d_name[strlen(dd -> d_name) - 1]) == 'e')
                && ((dd -> d_name[strlen(dd -> d_name) - 2]) == 'x')
                    && ((dd -> d_name[strlen(dd -> d_name) - 3]) == 'e')
                        && ((dd -> d_name[strlen(dd -> d_name) - 4]) == '.'))) {
            continue;
        }
        count ++;
    }
    closedir(d);
    printf("%lld\n", count);
    return 0;
}
