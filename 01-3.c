#include <stdio.h>
#include <stdlib.h>
enum
{
    PATH_MAX = 4097,
    DIGITS = 10
};
    int
    main(void)
    {
    int a;
    long long unsigned int *digit = (long long unsigned int*) malloc (DIGITS * sizeof(long long unsigned int));
    unsigned int c = 0, path_count = 0, i = 0;
    for(i = 0; i < DIGITS; i++){
        digit[i] = 0;}
        char *file_name = (char*) malloc ((PATH_MAX + 1) * sizeof(char));
        c = getchar_unlocked();
        while(c != EOF && c != '\r' && c != '\n' && path_count < PATH_MAX) {
            *(file_name + path_count) = c;
            path_count ++;
            c = getchar_unlocked();
    }
    *(file_name + path_count) = '\0';
    FILE *fp = NULL;
    fp = fopen(file_name,"r");
    if(fp != NULL) {
        a = fgetc_unlocked(fp);
        while (a != EOF) {
            if(a >= '0' && a <= '9'){
            digit[a - '0']++;}
            a = fgetc_unlocked(fp);
        }
    }
    if(fp != NULL){
        fclose(fp);
    }
    for(i = 0; i < DIGITS; i++){
        printf("%d %llu\n", i, digit[i]);
    }
    free(digit);
    free(file_name);
    return 0;
    }
