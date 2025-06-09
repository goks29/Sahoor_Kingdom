#ifndef Keluarga_h
#define Keluarga_h

#include "linked.h"
#include "queue.h"
#include "stack.h"
#include "nbtrees.h"

typedef struct {
    char type[20]; // LELUHUR, PASANGAN, ANAK, KELUARGA_PASANGAN, SAUDARA_PASANGAN
    char nama1[50];
    char nama2[50];
    char ayahName[50];
    char ibuName[50];
    int usia1;
    int gender1;
    int isHidup1;
    int usia2;
    int gender2;
    int isHidup2;
} FamilyData;

/*Prosedur Utama Kerajaan*/
void InsertLeluhur(NTree* tree);

void InsertPasangan(NTree* tree, char* NamaNode);

void InsertMember(NTree* tree, char* parentName);

void InsertKeluargaPasangan (NTree* tree, char* PartnerName);

void CetakHubungan(int gen1, int gen2, char* namaP1, char* namaP2, NkAdd lastCommon);

void CheckHubunganKeluarga(NTree tree);

void WarisHarta(NTree tree,char* parentName,int harta);

void HitungBagianWaris(Queue* Queue,NTree tree,char* parentName);

void printHarta(Qaddress Q,int harta,int *sisa);

void TimeSkip(NkAdd node, int year, NTree*);

void PrintSilsilah(NTree tree);

void CetakSilsilahPerGenerasi(NkAdd node, int level, boolean* adaYangDicetak, NkAdd root);

void PrintLevel(NkAdd root);


/*Prosedur file dan assets*/
void getDataFromFile(NTree* Tree);

void getFamilyFromFile(NTree* Tree);

void printFromFile(const char* location);

void ReadFamilyFromFile(FamilyData* data, int* count);

void UpdateFamilyData(FamilyData* existing, int* existingCount, FamilyData* newData, int newCount);

void WriteFamilyToFile(FamilyData* data, int count, int year);

void UpdateAges(NkAdd node, int year, NkAdd* visited, int* visitedCount);

void CollectFamilyData(NkAdd node, FamilyData* data, int* count, NkAdd* visited, int* visitedCount, NkAdd root);

/*fungsi pengecekan*/

int RangeUsiaAnak (NkAdd Ortu);

boolean IsDescendantOf(NkAdd node, NkAdd root);






#endif