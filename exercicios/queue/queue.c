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

myQueue* createQueue() {
	myQueue *q = (myQueue*)malloc(sizeof(myQueue));
	q->pFirst = NULL;
	q->pLast = NULL;
	return q;
}

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

int peek(myQueue *queue) {
	if (empty(queue)) {
		return -1;
	}

	return queue->pFirst->info;
}


void push(myQueue *queue, int data) {
	node *n = (node *)malloc(sizeof(node));

	n->info = data;
	n->next = NULL;

	if (empty(queue)) {
		queue->pFirst = n;
		queue->pLast = n;
	} else {
		queue->pLast->next = n;
		queue->pLast = n;
	}
}

int pop(myQueue *queue) {
	// queue is empty
	if (empty(queue)) {
		return -1;
	}
	int res;
	// queue is empty and has a single node
	if (queue->pFirst == queue->pLast) {
		res = queue->pFirst;
		reset(queue);
		return res;
	}

	node *temp = queue->pFirst;
	res = temp->info;
	queue->pFirst = queue->pFirst->next;
	free(temp);
	return res;
}
