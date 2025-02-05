#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define LIMIT 50

typedef struct node {
	int info;
	struct node *next;
} node;

typedef struct {
	node *pFirst;
	node *pLast;
} myQueue;

bool empty(myQueue *queue) {
	return queue->pLast == NULL;
}

// temp function for authenticating behaviour
void listAll(myQueue *queue) {
	node *p = queue->pFirst;

	while (p != NULL) {
		printf("node: %d\n", p->info);
		p = p->next;
	}
}

void reset(myQueue *queue) {

	if (queue == NULL) {
		return;
	}

	node *p = queue->pFirst;
	node *temp = NULL;

	while (p != NULL) {
		temp = p;
		p = p->next;

		free(temp);
	}

	queue->pLast = NULL;
	queue->pFirst = NULL;
}


void push(myQueue *queue, int *data) {
	node *n = (node *)malloc(sizeof(node));

	n->info = *data;
	n->next = NULL;

	if (empty(queue)) {
		queue->pFirst = n;
		queue->pLast = n;
	} else {
		queue->pLast->next = n;
		queue->pLast = n;
	}
}

void pop(myQueue *queue) {
	// queue is empty
	if (empty(queue)) {
		return;
	}
	// queue is empty and has a single node
	if (queue->pFirst == queue->pLast) {
		reset(queue);
		return;
	}

	node *temp = queue->pFirst;
	queue->pFirst = queue->pFirst->next;
	free(temp);
}
