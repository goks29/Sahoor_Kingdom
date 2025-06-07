#ifndef nbtrees_h
#define nbtrees_h

#include "linked.h"
#include "BOOLEAN.H"

/*TIPE DATA*/

typedef struct Nbtree {
    NkAdd root;
}NTree;

/*FUNGSI*/

void InitNbTree (NTree* T);

boolean IsEmptyTree (NTree* T);

void AddChild (NTree* T, NkAdd current, const char* parents, infotype name, int usia, boolean gender, boolean hidup);

NkAdd SearchNode (NkAdd curNode, const char* name);

int isVisited(NkAdd* visited, int count, NkAdd node);

NkAdd SearchNodeUniversal(NkAdd curNode, const char* name, NkAdd* visited, int* count);

void PrintTreeRek(NkAdd node, int level);

#endif
