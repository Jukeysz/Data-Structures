#include <stdlib.h>
#include <stdbool.h>

// use a priority queue
// I want the classes that have the LEAST difference between the pass,total
// I also want the total to be as smaller as possible

// by doing this I can reduce the overhead of each calculation in bruteforce

typedef struct classInfo {
    int a;
    int b;
    struct classInfo *next;
} classInfo;

typedef struct {
    classInfo *pFirst;
    classInfo *pLast;
} heap;

 heap* createQueue();
 bool empty(heap *q);
 classInfo push(heap *q, classInfo class);
 void reset(heap *q);
 heap* createQueue() {
     heap *q = (heap*)malloc(sizeof(heap));
     q->pFirst = NULL;
     q->pLast = NULL;
     return q;
 
 bool empty(heap *q) {
     return q->pFirst == NULL; 
 
 // insert at the correct position, not at the end
 classInfo push(heap *q, classInfo class) {
     if (empty(q)) return;
     classInfo *node = (classInfo*)malloc(sizeof(classInfo));
     node->a = class.a;
     node->b = class.b;
     node->next = NULL;
     // single element in the list
     if (q->pFirst == q->pLast) {
         int dif1 = q->pFirst->b - q->pFirst->a
         int dif2 = class.b - class.a
         if (dif1 > dif2) {
             node->next = q->pFirst;
             q->pFirst = node;
         } else {
             q->pFirst->next = node;
             q->pLast = node;
         }
     
     // insert in the beginning, middle or ending of the list
     classInfo *p = q->pFirst;
     classInfo *q = NULL;
     while (p != NULL) {
         classInfo max;
         max.a = 0;
         max.b = 0;
         max.next = NULL;
         int dif1 = p->b - p->a;
         int dif2 = node->b - node->a;
         if (dif1 < dif2) {
             max.a = p->a;
             max.b = p->b;
             max.next = p->next;
         } else {      
         }
         q = p;
         p = p->next;
     }
 
 void reset(heap *q) {
     if (empty(q)) return
     if (q->pLast == q->pFirst) {
         free(q->pLast);
         q->pFirst = NULL;
         q->pFirst = NULL;
     
     // TODO when there is more than a single elem( just pop stuff 
     while(pop(q));
     return;
 }

double maxAverageRatio(int** classes, int classesSize, int* classesColSize, int extraStudents) {
    // bruteforce
    
    double bestAverage = 0;
    for (int i = 0; i < classesSize; i++) { 
        int count = 0;
        double temp = (classes[i][0] + extraStudents) / classes[i][1];
        for (int j = 0; j < classesSize; j++) {
            if (i == j) {
                count += temp;
            }
            double t = (classes[j][0] + classes[j][1])/2;
            count += t;
        }

        double end = count/classesSize;
        if (end > bestAverage) {
            bestAverage = end;
        }
    }

    return bestAverage;
}

int main(void) {
    int *a = malloc(sizeof(int) * 2);
    *a = 1;
    *(a + 1) = 2;
    int *b = malloc(sizeof(int) * 2);
    *b = 3;
    *(b + 1) = 5;
    int *c = malloc(sizeof(int) * 2);
    *c = 3;
    *(c + 1) = 5;

    int **classes = malloc(sizeof(int*) * 3);
    classes[0] = a;
    classes[1] = b;
    classes[2] = c;

    int *l = malloc(sizeof(int*) * 3);
    int f = 2;
    int g = 2;
    int h = 2;
    a[0] = &f;
    a[1] = &g;
    a[2] = &h;

    double d = maxAverageRatio(classes, 3, l, 2);
}

