#ifndef Kingdom_h
#define Kingdom_h

#include "linked.h"
#include "queue.h"
#include "stack.h"
#include "nbtrees.h"
#include "Kingdom.h"

void InsertKing(NTree* tree);

void InsertPasangan(NTree* tree);

void InsertMember(NTree* tree);

void Generation();

void PrintSilsilah(NTree tree);

void TurunTahta();

void TimeSKip(NkAdd node, int year);

void getKingdomFromFile(NTree* Tree);

void getDataFromFile(NTree* Tree);

void printFromFile(const char* location);

void NextKing(NkAdd root);



#endif