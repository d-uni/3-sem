#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
long long int sum = 0;
int x;
char a[2] ="! ";
ssize_t n = 0;
while(n = read(0,&x,sizeof(x)) != 0) {
sum = sum + x;
write(1,&x,sizeof(x));
write(1,a,sizeof(a));
}
write(1,&sum,sizeof(sum));
    return 0;
}
