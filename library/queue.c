#include "queue.h"

void initQueue(Queue* Q) {
    Q->front = NULL;
    Q->rear = NULL;
}

boolean IsEmptyQueue(Queue* Q) {
    if (Q == NULL || Q->front == NULL) {
        return true;
    } else {
        return false;
    }
}

void EnQueue (Queue* Q, NkAdd node,double bagian) {
    QNode* NewNodeQ = (QNode*)malloc(sizeof(QNode));
    if (NewNodeQ != NULL) {
        NewNodeQ->data = node;
        NewNodeQ->bagianHarta = bagian;
        NewNodeQ->next = NULL;

        if (IsEmptyQueue(Q)) {
            Q->front = NewNodeQ;
            Q->rear = NewNodeQ;
        }

        if (!IsEmptyQueue(Q)) {
            Q->rear->next = NewNodeQ;
        }
    }
}

void DeQueue (Queue* Q, NkAdd node,double bagian) {
    if (!IsEmptyQueue(Q)) {
        Qaddress temp = Q->front;
        node = temp->data;
        Q->front = Q->front->next;

        if (Q->front == NULL) {
            Q->rear = NULL;
        }

        free(temp);
    }
}   
