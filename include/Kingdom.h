#ifndef Kingdom_h
#define Kingdom_h

#include "linked.h"
#include "queue.h"
#include "stack.h"
#include "nbtrees.h"

/*Prosedur Utama Kerajaan*/
void InsertKing(NTree* tree);

void InsertPasangan(NTree* tree, char* KingName);

void InsertMember(NTree* tree, char* parentName);

void CheckGeneration(NTree tree);

void PrintSilsilah(NTree tree);

void TurunTahta(NTree* tree, char* KingName);

void WarisHarta();

void NextKing(NkAdd root);

void TimeSKip(NkAdd node, int year);


/*Prosedur file dan assets*/
void getKingdomFromFile(NTree* Tree);

void getDataFromFile(NTree* Tree);

void printFromFile(const char* location);


/*fungsi pengecekan*/
boolean HasPartner(NkAdd node);

boolean IsKingExist(NTree* tree);






#endif