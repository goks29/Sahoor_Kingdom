#ifndef queue_h
#define queue_h
#include "linked.h"

/*TIPE DATA*/

typedef struct queueNode QNode;
typedef QNode* Qaddress;

typedef struct QNode {
    NkAdd data;
    Qaddress next;
}queueNode;

typedef struct {
    Qaddress front;
    Qaddress rear;
}Queue;


/*FUNGSI*/

void initQueue(Queue* Q);

boolean IsEmptyQueue(Queue* Q);

void EnQueue (Queue* Q, NkAdd node);

void DeQueue (Queue* Q, NkAdd node);



#endif