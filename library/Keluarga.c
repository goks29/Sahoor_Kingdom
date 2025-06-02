#include "Keluarga.h"

/*Prosedur Utama Kerajaan*/
void InsertLeluhur(NTree* tree) {

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
        getchar();

        strcpy(newRoot->Identitas.info, NamaLeluhur);
        newRoot->Identitas.Usia = usia;
        newRoot->Identitas.Gender = (boolean)gender;
        if(newRoot->Identitas.Usia > 110){
            newRoot->Identitas.IsHidup = 0;
        }else{
            newRoot->Identitas.IsHidup = 1;
        }
        
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

void InsertPasangan(NTree* tree, char* NamaNode) {
    
    char NamaPasangan[50];
    int umur;
    boolean gender,IsHidup;

    if(tree == NULL || tree->root == NULL){
        printf("Tree Belum Ada atau Root Kosong");
        return;
    }

    NkAdd TargetNode = SearchNode(tree->root,NamaNode);
    if(TargetNode == NULL){
        printf("%c Tidak Ditemukan Pada Tree",NamaNode);
        return;
    }

    if(!TargetNode->Identitas.IsHidup){
        printf("%c Sudah Meninggal masa mau dikawinin",NamaNode);
        return;
    }

    if(TargetNode->Pasangan != NULL){
        printf("%c sudah memiliki pasangan",NamaNode);
        return;
    }
    
    printf("Masukan Nama Pasangan dari %c : ",NamaNode);
    scanf(" %[^\n]",NamaPasangan);
    printf("Masukan Usia Pasangan %c : ",NamaNode);
    scanf("%d",&umur);
    if(TargetNode->Identitas.Gender == 1){
        gender = 0;
    }else{
        gender = 1;
    }

    PartAdd pasangan = CreateNPartner(NamaPasangan,umur,gender,IsHidup);
    if(pasangan == NULL){
        printf("Pasangan gagal dialokasi");
        return;
    }

    TargetNode->Pasangan = pasangan;

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
    FILE *file;
    char c;
    
    if (location == NULL) {
        return;
    }
    
    file = fopen(location, "rt");
    if (file == NULL) {
        return;
    }
    
    while ((c = fgetc(file)) != EOF) {
        printf("%c", c);
    }
    
    fclose(file);
}



/*fungsi pengecekan*/
boolean HasPartner(NkAdd node) {

}
