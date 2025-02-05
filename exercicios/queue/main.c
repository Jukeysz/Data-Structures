#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


int main( void ) {
    myQueue *q = (myQueue *)malloc(sizeof(myQueue));
    int a = 4;
    int b = 8;
    int c = 12;
    push(q, &a);
    push(q, &b);
    listAll(q);
    pop(q);
    listAll(q);
    pop(q);
    free(q);
}
