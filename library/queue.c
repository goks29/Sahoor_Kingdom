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

void EnQueue (Queue* Q, NkAdd node,double bagian,char* hubungan) {
    QNode* NewNodeQ = (QNode*)malloc(sizeof(QNode));
    if (NewNodeQ != NULL) {
        NewNodeQ->data = node;
        NewNodeQ->bagianHarta = bagian;
        strcpy(NewNodeQ->hubungan, hubungan);
        NewNodeQ->next = NULL;

        if (IsEmptyQueue(Q)) {
            Q->front = NewNodeQ;
            Q->rear = NewNodeQ;
        }else{
            Q->rear->next = NewNodeQ;
            Q->rear = NewNodeQ;
        }
    }
}

void DeQueue (Queue* Q, NkAdd node) {
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
