#ifndef queue_h
#define queue_h
#include "linked.h"

/*TIPE DATA*/

typedef struct QNode* Qaddress;

typedef struct QNode {
    NkAdd data;
    double bagianHarta;
    struct QNode* next;
} QNode;

typedef struct {
    Qaddress front;
    Qaddress rear;
} Queue;


/*FUNGSI*/

void initQueue(Queue* Q);

boolean IsEmptyQueue(Queue* Q);

void EnQueue (Queue* Q, NkAdd node,double bagian);

void DeQueue (Queue* Q, NkAdd node,double bagian);



#endif