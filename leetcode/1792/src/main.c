#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int pass;
    int total;
    double ratio;
    int index;
    struct node *next;
} node;

typedef struct {
    node *pFirst;
    node *pLast;
} queue;

void reset(queue *q);
queue* createQueue();
bool empty(queue *q);
void push(queue *q, int pass, int total, int ind);
int peek(queue *q);
double takeAvg(int pass, int total);
double takeAvgRatio(double avg1, double avg2);
node* extractBest(queue* q);

double maxAverageRatio(int** classes, int classesSize, int* classesColSize, int extraStudents) {
    queue *q = createQueue();

    // original class data
    for (int i = 0; i < classesSize; i++) {
        push(q, classes[i][0], classes[i][1], i);
    }

    for (int i = 0; i < extraStudents; i++) {
        // class with the best ratio
        node *best = extractBest(q);
        if (!best) break;

        int ind = best->index;
        classes[ind][0]++;
        classes[ind][1]++;

        // reinsert the updated class
        push(q, classes[ind][0], classes[ind][1], ind);
        free(best);
    }

    // calculate final avg 
    double count = 0.0;
    for (int i = 0; i < classesSize; i++) {
        count += takeAvg(classes[i][0], classes[i][1]);
    }

    reset(q);
    free(q);
    return count/classesSize;
}

node* extractBest(queue* q) {
    if (empty(q)) return NULL;
    node *prevBest = NULL; 
    node *best = q->pFirst;
    node *curr = q->pFirst;
    node *prev = NULL;

    // find the node with highest ratio
    while (curr) {
        if (curr->ratio > best->ratio) {
            best = curr;
            prevBest = prev;
        }
        prev = curr;
        curr = curr->next;
    }

    // remove best node
    if (prevBest) {
        prevBest->next = best->next;
    } else {
        q->pFirst = best->next;
    }

    if (!q->pFirst) {
        q->pLast = NULL;
    }

    best->next = NULL;
    return best;
}

void push(queue *q, int pass, int total, int ind) {
    // one student at a time!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    node *n = (node*)malloc(sizeof(node));

    n->pass = pass;
    n->total = total;
    n->next = NULL;
    n->index = ind;

    double avg1 = takeAvg(pass, total);
    double avg2 = takeAvg(pass + 1, total + 1);
    double rat = takeAvgRatio(avg1, avg2);

    n->ratio = rat;

    if (empty(q)) {
        q->pFirst = n;
        q->pLast = n;
        return;
    }

    // iterate over the classes, and find the right place according to ratio
    node *curr = q->pFirst;
    node *prev = NULL;

    // find correct spot, stop when it finds a node that has smaller ratio than n
    while (curr != NULL && n->ratio < curr->ratio) {
        prev = curr;
        curr = curr->next;
    }

    // edge case where I have to insert in the end
    if (curr == NULL) {
        q->pLast->next = n;
        q->pLast = n;
        return;
    }

    // edge case where I have to insert in the beginning
    if (curr == q->pFirst) {
        n->next = q->pFirst;
        q->pFirst = n;
        return;
    }

    // middle of the list
    prev->next = n;
    n->next = curr;
    return;
}

bool empty(queue *q) {
    return q->pLast == NULL;
}

queue* createQueue() {
    queue *q = (queue*)malloc(sizeof(queue));
    q->pFirst = NULL;
    q->pLast = NULL;
    return q;
}

// dont use pop right away for simplicity matters
void reset(queue *q) {
    if (empty(q)) return;

    node *n = q->pFirst;
    node *temp = NULL;

    while (n != NULL) {
        temp = n;
        n = n->next;
        free(temp);
    }

    q->pFirst = NULL;
    q->pLast = NULL;

    return;
}

double takeAvg(int pass, int total) {
    return (double)pass/(double)total;
}

double takeAvgRatio(double avg1, double avg2) {
    return avg2 - avg1;
}