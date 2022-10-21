#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

int myaccess(const struct stat *stb, const struct Task *task, int access)
{
    if(task -> uid == 0) {
        return 0;
    }
    unsigned int owner = stb -> st_mode >> (unsigned)6;
    owner = owner & access;
    if(stb -> st_uid == task -> uid) {
        if(owner == access) {
            return 1;
        } else {
            return 0;
        }
    }
    int i = 0;
    unsigned int group = 0;
    for(i = 0; i < task -> gid_count; i++) {
        if(stb -> st_gid == task -> gids[i]) {
            group = stb -> st_mode >> (unsigned)3;
            group = group & access;
            if(group == access) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    if((stb -> st_mode & access) == access) {
        return 1;
    } else {
        return 0;
    }
}
