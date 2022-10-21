#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

int
main(int argc, char *argv[])
{
    char *path_t;
    if((path_t = getenv("XDG_RUNTIME_DIR"))) {
    } else if ((path_t = getenv("TMPDIR"))) {
    } else {
        path_t = calloc(5, sizeof(char));
        path_t = "/tmp";
    }
    char *go = calloc(PATH_MAX, sizeof(*go));
    snprintf(go, PATH_MAX, "%s/%s", path_t, "apb.py");
    int fd = open(go, O_CREAT | O_WRONLY | O_TRUNC, 0777);
    char s[] = "#!/bin/env python3\nprint(";
    dprintf(fd, "%s", s);
    for (int i = 1; i < argc; i++) {
        dprintf(fd, "%s", argv[i]);
        if(i != argc - 1) {
            dprintf(fd, "%s", "*");
        }
    }
    dprintf(fd, "%s", ")");
    close(fd);
    execlp(go, go, NULL);
    return 0;
}
