#include <stdbool.h>

#define LIMIT 500

typedef struct student_t {
    char name[50];
    int ra;
} student_t;

typedef struct stack_t {
    student_t *students;
    student_t *top;
    student_t *base;
    int limit;
} stack_t;

/*
============================================
Reset
    Clear every remaining item in the stack
============================================
*/
void Reset(stack_t *stk);

/*
============================================
Push
    Place an element over the stack
============================================
*/
bool Push(stack_t *stk, student_t *student);

/*
============================================
Pop
    Remove an element from the stack
============================================
*/
bool Pop(stack_t *stk);

/*
============================================
Empty
    Check if the stack is empty
============================================
*/
void Empty(stack_t *stk);

/*
============================================
List
    List every single element in the stack, from top to
    bottom
============================================
*/
void List(stack_t *stk);

/*
============================================
Full
    Check if the list is full
============================================
*/
bool Full(stack_t *stk);