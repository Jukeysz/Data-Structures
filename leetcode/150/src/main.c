#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int *stk;
    int *top;
    int *bot;
    int limit;
} myStack;

void Reset(myStack *stack);
bool Empty(myStack *stack);
bool Full(myStack *stack);
int Push(myStack *stack, int item);
int Pop(myStack *stack);
int Peek(myStack *stack);
int evalRPN(char **tokens, int tokensSize);

int main() {
    char **tokens = malloc(sizeof(char *) * 3);
    char *a = "4";
    char *b = "3";
    char *c = "-";
    tokens[0] = a;
    tokens[1] = b;
    tokens[2] = c;
    int result = evalRPN(tokens, 3);
    printf("Result: %d\n", result);
}

int evalRPN(char** tokens, int tokensSize) {
    myStack *stack = malloc(sizeof(myStack));
    Reset(stack);

    int end = stack->limit;

    for (int i = 0; i < tokensSize; i++) {
        if (strcmp(tokens[i], "+") == 0) {
            int a = Pop(stack);
            int b = Pop(stack);
            Push(stack, a + b);
        } else if (strcmp(tokens[i], "-") == 0) {
            int a = Pop(stack);
            int b = Pop(stack);
            Push(stack, a - b);
        } else if (strcmp(tokens[i], "*") == 0) {
            int a = Pop(stack);
            int b = Pop(stack);
            Push(stack, a * b);
        } else if (strcmp(tokens[i], "/") == 0) {
            int a = Pop(stack);
            int b = Pop(stack);
            Push(stack, b / a);
        } else {
            Push(stack, atoi(tokens[i]));
        }
    }

    return *(stack->top);
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

int Push(myStack *stack, int item) {
    if (stack->limit != 0) {
        int *new = (int *)realloc(stack->stk, sizeof(int) * (stack->limit + 1));
        if (new == NULL) {
            printf("Failed to allocate memory\n");
            return 0;
        }
        stack->stk = new;
        stack->top = stack->stk + stack->limit;
        stack->limit++;
    } else {
        int *new = malloc(sizeof(int));
        if (new == NULL) {
            printf("Failed to allocate memory\n");
            return false;
        }

        stack->stk = new;
        stack->top = stack->stk;
        stack->bot = stack->stk;
        stack->limit++;
    }

    // memcpy(stack->top, item, sizeof(int));
    *(stack->top) = item;
    return 1;
}

int Pop(myStack *stack) {
    if (stack->limit != 0) {
        int old = *(stack->top);
        int *new = realloc(stack->stk, sizeof(int) * (stack->limit - 1));
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
    return -1;
}

int Peek(myStack *stack) {
    if (stack->limit != 0) {
        return *(stack->top);
    } else {
        return -1;
    }
}

