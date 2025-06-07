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

void InsertKeluargaPasangan (NTree* tree, char* PartnerName);

void CheckHubunganKeluarga(NTree tree);

void WarisHarta(NTree tree,char* parentName);

void TimeSkip(NkAdd node, int year);

void PrintSilsilah(NTree tree);

void CetakSilsilahPerGenerasi(NkAdd node, int level, boolean* adaYangDicetak);

void PrintLevel(NkAdd root);


/*Prosedur file dan assets*/
void getDataFromFile(NTree* Tree);

void getFamilyFromFile(NTree* Tree);

void printFromFile(const char* location);

/*fungsi pengecekan*/

int RangeUsiaAnak (NkAdd Ortu);







#endif