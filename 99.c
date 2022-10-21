#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int
main(void)
{
int PATH_MAX = 4097;
int DIGITS = 10;
ssize_t count = 0;
long long unsigned int *digit = (long long unsigned int*) malloc (DIGITS * sizeof(long long unsigned int));
char a;
unsigned int c = 0, path_count = 0, i = 0, file_exists = 0;
for(i = 0;i < DIGITS; i++){
    digit[i] = 0;}
    char *file_name = (char*) malloc ((PATH_MAX + 1) * sizeof(char));
    c=getchar_unlocked();
    while(c != EOF && c != '\r' && c != '\n' && path_count < PATH_MAX) {
        *(file_name + path_count) = c;
        path_count ++;
        c = getchar_unlocked();
}
*(file_name + path_count) = '\0';
int fd = open(file_name,O_RDONLY,0444);
if(fd != -1) {
    while((count = read(fd, &a, sizeof(a))) > 0) {
        if(a >= '0' && a <= '9'){
        digit[a - '0']++;}
}
file_exists = 1;
}
if(file_exists){
    close(fd);
}
for(i = 0; i < DIGITS - 1; i++){
    printf("%d %llu\n", i, digit[i]);
}
printf("%d %llu", DIGITS - 1, digit[DIGITS - 1]);
free(digit);
free(file_name);
return 0;
}
