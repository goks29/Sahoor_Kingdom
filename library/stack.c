#include "stack.h"

void InitStack(Stack* S) {
    S->top = NULL;
}

boolean IsEmptyStack(Stack* S) {
    if (S->top == NULL) {
        return true;
    } else {
        return false;
    }
}

void Push(Stack* S, StackItem Node) {
    StackNode* newNodeS = (StackNode*)malloc(sizeof(StackNode));
    if (newNodeS != NULL) {
        newNodeS->data = Node;
        newNodeS->next = S->top;
        S->top = newNodeS;
    }
}

StackItem Pop(Stack* S) {
    StackItem item;
    if (!IsEmptyStack(S)) {
        StackNode* temp = S->top;
        item = temp->data;
        S->top = temp->next;
        free(temp);
        return item;
    } else {
        item.data = NULL;
        item.generation = -1;
        return item;
    }
}
