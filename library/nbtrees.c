#include "nbtrees.h"

void InitNbTree (NTree* T) {
    T->root = NULL;
}

boolean IsEmptyTree (NTree* T){
    return (T->root == NULL);
}

void AddChild (NTree* T, const char* parents, infotype name, int usia, boolean gender, boolean hidup) {
    int i=2;
    if (IsEmptyTree(T)) {
        T->root = CreateNode(NULL, name, usia, gender, hidup);
        return;
    } 

    NkAdd current = SearchNode(T->root,parents);
    if (current != NULL && current->Pasangan != NULL ) {
        NkAdd newChild = CreateNode(current, name, usia, gender, hidup);

        if (current->FirstSon == NULL) {
            current->FirstSon = newChild;
            if (current->Pasangan != NULL) {
                current->Pasangan->FirstSon = newChild;
            }
            printf("%s merupakan first son dari %s dan %s\n",name,parents,current->Pasangan->Identitas.info);
        } else {
            NkAdd temp = current->FirstSon;
            while (temp->NextBrother != NULL) {
                temp = temp->NextBrother;
                i++;
            }
            temp->NextBrother = newChild;
            printf("%s merupakan anak ke-%d dari %s dan %s\n\n",name,i,current->Identitas.info,current->Pasangan->Identitas.info);
        } 
    } else {
        printf("Parents '%s' tidak ditemukan atau node yang dicari belum menikah", parents);
    }
}

NkAdd SearchNode (NkAdd curNode, const char* name) {
    if (curNode == NULL) {
        return NULL;
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

int isVisited(NkAdd* visited, int count, NkAdd node) {
    for (int i = 0; i < count; i++) {
        if (visited[i] == node) return 1;
    }
    return 0;
}

NkAdd SearchNodeUniversal(NkAdd curNode, const char* name, NkAdd* visited, int* count) {
    if (curNode == NULL || isVisited(visited,*count,curNode)) {
        return NULL;
    }

    visited[(*count)++] = curNode;

    if (strcmp(curNode->Identitas.info,name) == 0 ) {
        return curNode;
    }

    NkAdd found = NULL;

    
    found = SearchNodeUniversal(curNode->Pasangan,name,visited,count);
    if (found) {
        return found;
    }

    found = SearchNodeUniversal(curNode->FirstSon,name,visited,count);
    if (found) {
        return found;
    }

    found = SearchNodeUniversal(curNode->NextBrother,name,visited,count);
    if (found) {
        return found;
    }
    
    found = SearchNodeUniversal(curNode->Parents,name,visited,count);
    if (found) {
        return found;
    }

    return NULL;
}

void PrintTreeRek(NkAdd node, int level) {
    if (node == NULL) return;

    for (int i = 0; i < level; i++) printf("  ");
    printf("- %s (%d)\n", node->Identitas.info, node->Identitas.Usia);

    if (node->Pasangan != NULL) {
        for (int i = 0; i < level; i++) printf("  ");
        printf("  + Pasangan: %s (%d)\n", node->Pasangan->Identitas.info, node->Pasangan->Identitas.Usia);
    }

    PrintTreeRek(node->FirstSon, level + 1);
    PrintTreeRek(node->NextBrother, level);
}

void PrintTree(NTree T) {
    if (T.root == NULL) {
        printf("Pohon kosong.\n");
    } else {
        PrintTreeRek(T.root, 0);
    }
}