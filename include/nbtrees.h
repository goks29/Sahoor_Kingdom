#ifndef nbtrees_h
#define nbtrees_h
#include "linked.h"

/*TIPE DATA*/

typedef struct Nbtree {
    NkAdd* root;
    NkAdd* Raja;
}NTree;

/*FUNGSI*/

void InitNbTree (NTree* T);

boolean IsEmptyTree (NTree* T);

void AddChild (NTree* T, NkAdd child);

NkAdd SearchNode (NTree* T, const char* name);

void PrintTree (NTree T);


#endif
