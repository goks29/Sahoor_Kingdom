#include "Keluarga.h"

/*Prosedur Utama Kerajaan*/
void InsertLeluhur(NTree* tree) {

    if(IsEmptyTree){
        printf("Tree Belum Ada");
        return;
    }
    if(!IsEmptyTree){
        printf("Tree Sudah Memiliki root");
        return;
    }

    NkAdd newRoot = (NkAdd)malloc(sizeof(NodeK));
    if(newRoot == NULL){
        printf("Alokasi Root Gagal DIlakukan");
        return;
    }

    char NamaLeluhur[50];
    int usia, gender, isHidup,prosespilih;

    do{
        printf("Masukkan nama leluhur: ");
        scanf(" %[^\n]", NamaLeluhur);
        getchar();
        printf("Masukkan usia: ");
        scanf("%d", &usia);
        printf("Masukkan gender (1 = Pria, 0 = Wanita): ");
        scanf("%d", &gender);
        printf("Apakah masih hidup? (1 = Ya, 0 = Tidak): ");
        scanf("%d", &isHidup);
        getchar();

        strcpy(newRoot->Identitas.info, NamaLeluhur);
        newRoot->Identitas.Usia = usia;
        newRoot->Identitas.Gender = (boolean)gender;
        newRoot->Identitas.IsHidup = (boolean)isHidup;   
        
        printf("Apakah Input Sudah Benar(1 = ya, 2 = tidak) : ");
        scanf("%d",&prosespilih);
    } while (prosespilih == 2);
    
    newRoot->FirstSon = NULL;
    newRoot->NextBrother = NULL;
    newRoot->Parents = NULL;
    newRoot->Pasangan = NULL;
    tree->root = newRoot;   
    printf("Leluhur berhasil ditambahkan");
    return;
}

void InsertPasangan(NTree* tree, char* KingName) {
    
    if(tree == NULL || tree->root == NULL){
        printf("Tree Belum Ada atau Root Kosong");
        return;
    }

}

void InsertMember(NTree* tree, char* parentName) {

}

void CheckKoneksiKeluarga(NTree tree) {

}

void PrintSilsilah(NTree tree) {

}

void WarisHarta() {

}

void TimeSkip(NkAdd node, int year) {

}


/*Prosedur file dan assets*/
void getDataFromFile(NTree* Tree) {

}

void printFromFile(const char* location) {

}


/*fungsi pengecekan*/
boolean HasPartner(NkAdd node) {

}
