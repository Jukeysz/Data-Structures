#include <stdbool.h>

#define LIMIT 500

typedef struct node {
	int info;
	struct node *next;
} node;

typedef struct {
	node *pFirst;
	node *pLast;
} myQueue;

bool empty(myQueue *queue);

void listAll(myQueue *queue);

void reset(myQueue *queue);

void push(myQueue *queue, int *data);

void pop(myQueue *queue);