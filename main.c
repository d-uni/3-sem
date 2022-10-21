#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
int main()
{
    char b[16] = {};
    int x = 0, i, j;
    int n = 0;
    long long int sum = 0;
    while((n = read(0, b, sizeof(b))) != 0){
        if(n == -1) {exit(errno);}
        for(i = 0; i < n; i++){
        printf("%d! ",b[i] - '0');
            if(b[i] != ' ') {
            if(b[i] == '-') {
            x = b[i+1] - '0';
            for(j = i+2; b[j] != ' ' && b[j] != '\n' && j < n; j++){
                    x = x * 10;
                    x = x + b[j]-'0';
                }
                x = -x;
            } else if(b[i] == '+') {
                x = b[i+1] - '0';
                for(j = i+2; b[j] != ' ' && b[j] != '\n' && j < n; j++){
                x = x * 10;
                x = x + b[j]-'0';

                }
            } else {
               x = b[i] - '0';
               for(j = i+1; b[j] != ' ' && b[j] != '\n' && j < n; j++){
               x = x * 10;
                x = x + (b[j]-'0');
                }
            }
            i = j;

            sum = sum + x;
            printf("    %lld= \n", sum);
         }
    }
    }
    printf("%lld\n",sum);
    return 0;
}
