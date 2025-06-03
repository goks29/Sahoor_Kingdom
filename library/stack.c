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

void Push(Stack* S, NkAdd Node) {
    StackNode* newNodeS = (StackNode*)malloc(sizeof(StackNode));
    if (newNodeS != NULL) {
        newNodeS->data = Node;
        newNodeS->next = S->top;
        S->top = newNodeS;
    }
}

NkAdd Pop(Stack* S) {
    NkAdd item;
    if (!IsEmptyStack(S)) {
        StackNode* temp = S->top;
        item = temp->data;
        S->top = temp->next;
        free(temp);
        return item;
    } else {
        item = NULL;
        return item;
    }
}
