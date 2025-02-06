#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct {
    myQueue *q;
} myStack;

myStack *createStack();
void stackPush(myStack *stack, int x);
int stackPop(myStack *stack);

int main( void ) {
    myStack *stk = (myStack *)malloc(sizeof(myStack));
   
}

myStack* createStack() {
    myStack *stk = (myStack*)malloc(sizeof(myStack));
    stk->q = createQueue();
    return stk;
}

void stackPush(myStack *stack, int x) {
    push(stack->q, x);

    // rotate the queue to make the new element front
    // we are assuring that the top of the stack stays
    // at the beginning of the linked list
    int size = 0;
    node *current = stack->q->pFirst;

    while (current != NULL) {
        size++;
        current = current->next;
    }

    for (int i = 0; i < size - 1; i++) {
        push(stack->q, pop(stack->q));
    }
}

int stackPop(myStack *stack) {
    return pop(stack->q);
}
