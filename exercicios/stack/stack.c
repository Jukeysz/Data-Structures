#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void Reset(stack_t *stk) {
    stk->students = NULL;
    stk->top = NULL;
    stk->base = NULL;
    stk->limit = 0;
}

bool Push(stack_t *stk, student_t *student) {
    if (stk->limit != 0) {
        realloc(stk->students, sizeof(student_t) * stk->limit + 1);
        if (stk->students == NULL) {
            printf("Memory allocation error");
            return 1;
        }

        stk->top++;
        stk->limit++;
        memcpy(stk->top, student, sizeof(student_t));
        return true;
    } else {
        stk->students = malloc(sizeof(student_t));
        if (stk->students == NULL) {
            printf("Memory allocation error");
            return 1;
        }
        
        stk->limit++;
        stk->base = stk->students;
        stk->top = stk->students;
        return true;
    }
    return false;
}
