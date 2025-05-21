#ifndef stack_h
#define stack_h
#include "linked.h"

/*TIPE DATA*/

typedef struct StackNode* Saddress;

typedef struct SNode {
    NkAdd data;
    struct SNode* next;
} StackNode;

typedef struct {
    Saddress top;
}Stack;

/*FUNGSI*/

void InitStack(Stack* S);

boolean IsEmptyStack(Stack* S);

void Push(Stack* S, NkAdd Node);

void Pop(Stack* S, NkAdd Node);



#endif