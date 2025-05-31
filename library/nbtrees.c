#include "nbtrees.h"

void InitNbTree (NTree* T) {
    T->root = NULL;
}

boolean IsEmptyTree (NTree* T){
    return (T->root == NULL);
}

void AddChild (NTree* T, const char* parents, infotype name, int usia, boolean gender, boolean hidup) {
    if (IsEmptyTree) {
        T->root = CreateNode(NULL,name,usia,gender,hidup);
        return;
    } 

    NkAdd current = SearchNode(T->root,parents);
    if (current != NULL && current->Pasangan != NULL ) {
        NkAdd newChild = CreateNode(current, name, usia, gender, hidup);

        if (current->FirstSon == NULL) {
            current->FirstSon = newChild;
        } else {
            NkAdd temp = current->FirstSon;
            while (temp->NextBrother != NULL) {
                temp = temp->NextBrother;
            }
            temp->NextBrother = newChild;
        } 
    } else {
        printf("Parents tidak ditemukan atau node yang dicari belum menikah");
    }
}

NkAdd SearchNode (NkAdd curNode, const char* name) {
    if (curNode == NULL) {
        return;
    } 

    if (strcmp(curNode->Identitas.info, name) == 0) {
        return curNode;
    }
    
    if (curNode->Pasangan != NULL && strcmp(curNode->Pasangan->Identitas.info,name) == 0) {
        return curNode;
    }

    NkAdd found = SearchNode(curNode->FirstSon,name);
    if (found != NULL) {
        return found;
    }

    return SearchNode(curNode->NextBrother,name);
    
}

void PrintTree (NTree T) {
    
}