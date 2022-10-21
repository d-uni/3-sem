#include <stdio.h>
 #include <stdlib.h>
 int main(int x)
 {int reject = 1; int summon = 2; int disqualify = 3;
while((scanf("%d", &x)) > 0) {
 int answ = x ;
 if(answ == 1) printf("reject\n");
if(answ == 2) printf("summon\n");
if(answ == 3) printf("disqualify\n");
}
}
