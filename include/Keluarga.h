#ifndef Keluarga_h
#define Keluarga_h

#include "linked.h"
#include "queue.h"
#include "stack.h"
#include "nbtrees.h"

/*Prosedur Utama Kerajaan*/
void InsertLeluhur(NTree* tree);

void InsertPasangan(NTree* tree, char* NamaNode);

void InsertMember(NTree* tree, char* parentName);

void CheckHubunganKeluarga(NTree tree);

void PrintSilsilah(NTree tree);

void WarisHarta(NTree tree,char* parentName);

void TimeSkip(NkAdd node, int year);


/*Prosedur file dan assets*/
void getDataFromFile(NTree* Tree);

void printFromFile(const char* location);


/*fungsi pengecekan*/
boolean HasPartner(NkAdd node);

boolean IsLeluhurExist(NTree* tree);







#endif