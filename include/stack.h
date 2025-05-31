#ifndef stack_h
#define stack_h
#include "linked.h"

/*TIPE DATA*/

typedef struct StackNode* Saddress;

typedef struct {
    NkAdd data;
}StackItem;

typedef struct StackNode {
    StackItem data;
    Saddress next;
} StackNode;

typedef struct {
    Saddress top;
}Stack;

/*FUNGSI*/

void InitStack(Stack* S);

boolean IsEmptyStack(Stack* S);

void Push(Stack* S, StackItem Node);

StackItem Pop(Stack* S);



#endif