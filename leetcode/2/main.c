#include <stdio.h>
#include <stdlib.h>

typedef struct listNode_t {
    int val;
    struct listNode_t *next;
} listNode_t;

struct listNode_t* addTwoNumbers(struct listNode_t* l1, struct listNode_t* l2);

int main( void ) {
    listNode_t *headNum1 = NULL;
    listNode_t *headNum2 = NULL;

    int op1 = 0;
    int op2 = 0;

    while (1) {
        printf("Insira o op1: ");
        scanf("%d", &op1);
        if ( op1 < 0 || op1 > 9 ) {
            break;
        }
        listNode_t *new = malloc(sizeof(listNode_t));
        if ( new == NULL ) {
            printf("malloc failed");
            return 1;
        }
        new->val = op1;
        new->next = NULL;

        if ( headNum1 == NULL ) {
            headNum1 = new;
        } else {
            listNode_t *p = NULL;
            for (p = headNum1; p->next != NULL; p = p->next);
            p->next = new;
        }
    }
    while (1) {
        printf("Insira o op2: ");
        scanf("%d", &op2);
        if ( op2 < 0 || op2 > 9 ) {
            break;
        }
        listNode_t *new = malloc(sizeof(listNode_t));
        if ( new == NULL ) {
            printf("malloc failed");
            return 1;
        }
        new->val = op2;
        new->next = NULL;

        if ( headNum2 == NULL ) {
            headNum2 = new;
        } else {
            listNode_t *p = NULL;
            for (p = headNum2; p->next != NULL; p = p->next);
            p->next = new;
        }
    }

    listNode_t *headResult = NULL;

    headResult = addTwoNumbers(headNum1, headNum2);

    for ( listNode_t *p = headResult; p != NULL; p = p->next ) {
        printf("%d", p->val);
    }
    printf("\n");
}

listNode_t* recursiveAddTraverse(listNode_t *l1, listNode_t *l2, int carry) {
    if (!l1 && !l2 && carry == 0) {
        return NULL;
    }

    int val1 = (l1) ? l1->val : 0;
    int val2 = (l2) ? l2->val : 0;

    int sum = val1 + val2 + carry;
    carry = (int)sum / 10;
    sum = sum % 10;

    listNode_t *new = malloc(sizeof(listNode_t));
    if (new == NULL) {
        printf("malloc failed\n");
        exit(1);
    }
    new->val = sum;

    new->next = recursiveAddTraverse(
        (l1) ? l1->next : NULL,
        (l2) ? l2->next : NULL,
        carry
    );

    return new;
}

struct listNode_t* addTwoNumbers(struct listNode_t* l1, struct listNode_t* l2) {
    return recursiveAddTraverse(l1, l2, 0);
}