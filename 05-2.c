#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int
main(int argv, char **argc)
{
    char s[9] = {"rwxrwxrwx"};
    int umask ;
    int i;
    for(int j = 1 ;j < argv; j++) {
    char* p_end;
    long long int x = strtol(argc[j], &p_end, 8);
    umask =1 << 8;
    for(i = 0; i < 9; i++) {
        if((umask & x) != 0) {
            printf("%c", s[i]);
            } else { printf("-");}
        umask = umask>>1;
        }
        printf("\n");
    }
    return 0;
}