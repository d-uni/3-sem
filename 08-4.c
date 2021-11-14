#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <string.h>

struct argument {
    char args[64];
};

int
main(int argc, char **argv)
{
    char *p;
    int x, j = 0;
    double d;
    char **c;
    struct argument a;
    for (int i = 1; i < argc; i++) {
        if(argv[3][i] == 'i') {
            x = strtol(argv[3 + i],  &p, 10);
            memcpy(&a.args[j], (char *)&x, 4);
            j = j + 4 + 1;
        } else if(argv[3][i] == 'd') {
            d = strtod(argv[3 + i], &p);
            memcpy(&a.args[j], (char *)&d, 8);
            j = j + 8 + 1;
        } else if(argv[3][i] == 's') {
            c = &argv[3 + i];
            memcpy(&a.args[j], *c, sizeof(&argv[3 + i]));
            j = j + sizeof(argv[3 + i]) + 1;
        }
    }

    void *handle;
    float (*func)(struct argument);
    char *error;

    handle = dlopen(argv[1], RTLD_LAZY);
    if(!handle) {
        printf("error\n");
        return 0;
    }
    func = dlsym(handle, argv[2]);
    error = dlerror();
    if(error != NULL) {
        printf("error\n");
        return 0;
    }
    if(argv[3][0] == 'i') {
        printf("%d\n", (*func)(a));
    } else if(argv[3][0] == 'd') {
        printf("%.10g\n", (*func)(a));
    } else if(argv[3][0] == 's') {
        printf("%s\n", (*func)(a));
    }
    dlclose(handle);
    return 0;
}
