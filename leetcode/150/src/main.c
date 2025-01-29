#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char *stk;
    char *top;
    char *bot;
    int limit;
} myStack;

void Reset(myStack *stack);
bool Empty(myStack *stack);
bool Full(myStack *stack);
bool Push(myStack *stack, char *item);
char Pop(myStack *stack);
char Peek(myStack *stack);

int main(int argc, char const *argv[])
{
    myStack *pilha = (myStack *)malloc(sizeof(myStack));
    Reset(pilha);

    char a = 'a';
    char b = 'b';
    char c = 'c';

    Push(pilha, &a);
    Push(pilha, &b);
    Push(pilha, &c);

    char x = Pop(pilha);
    char y = Pop(pilha);
    char z = Pop(pilha);

    return 0;
}

void Reset(myStack *stack) {
    stack->stk = NULL;
    stack->top = NULL;
    stack->bot = NULL;
    stack->limit = 0;
}

bool Empty(myStack *stack) {
    return stack->stk == NULL;
}

bool Full(myStack *stack) {
    return stack->top == stack->stk + (stack->limit - 1);
}

bool Push(myStack *stack, char *item) {
    if (stack->limit != 0) {
        char *new = (char *)realloc(stack->stk, sizeof(char) * (stack->limit + 1));
        if (new == NULL) {
            printf("Failed to allocate memory\n");
            return 0;
        }
        stack->stk = new;
        stack->top = stack->stk + stack->limit;
        stack->limit++;
    } else {
        char *new = malloc(sizeof(char));
        if (new == NULL) {
            printf("Failed to allocate memory\n");
            return false;
        }

        stack->stk = new;
        stack->top = stack->stk;
        stack->bot = stack->stk;
        stack->limit++;
    }

    memcpy(stack->top, item, sizeof(char));
    return true;
}

char Pop(myStack *stack) {
    if (stack->limit != 0) {
        int old = *(stack->top);
        char *new = realloc(stack->stk, sizeof(char) * (stack->limit - 1));
        if (new == NULL) {
            Reset(stack);
            return old;
        }
        stack->stk = new;
        stack->limit--;
        stack->bot = stack->stk;
        stack->top = stack->stk + (stack->limit - 1);
        //stack->limit--;
        return old;
    } 
    printf("No elements to be removed!\n");
    return false;
}

char Peek(myStack *stack) {
    if (stack->limit != 0) {
        return *(stack->top);
    }
}
