#include <stdio.h>
#include <stdlib.h>
#include  <float.h>
typedef struct num {
    double d;
    int i;
    struct num *next;
} num;
num *create_node(int x1, double x2) {
    num *node  = (num *)malloc(sizeof(num));
    node -> d = x2;
    node -> i = x1;
    node -> next = NULL;
    }
void push(num **node, double x1, int x2)
{
    num *y = *node;
    num *y_next = *node;
    while(y_next != NULL && y_next -> d <= x1) {
        y = y_next;
        y_next = y_next -> next;
        }
    num *new_node = create_node(x2, x1);
    if((y_next) != NULL){
    new_node -> next = y_next;
    }
    y -> next = new_node;
}
int
main(void)
{
    double d = 0;
    int i = 0;
    d = -DBL_MAX;
    num *root = create_node(d,0);

    scanf("%lf %d",&d,&i);
    push(&root, d, i);
    while(scanf("%lf %d",&d,&i) > 0){
    push(&root, d, i);
    }
    while(root -> next != NULL){
    root = root -> next;
    printf("%.10g %d\n", root -> d, root -> i);
    }
    return 0;
}
