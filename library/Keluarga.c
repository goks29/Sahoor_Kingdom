#include "Keluarga.h"

/*Prosedur Utama Keluarga*/
void InsertLeluhur(NTree* tree) {
    FILE* file = fopen("db/Family.txt","a");

    if (file == NULL) {
        printf("File tidak dapat dibuka");
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
    
    if (file != NULL) {
        fprintf(file, "NULL, %s, %d, %d",newRoot->Identitas.info,newRoot->Identitas.Usia,newRoot->Identitas.Gender);
    }
    fclose(file);
    return;
}

void InsertPasangan(NTree* tree, char* NamaNode) {
    
    char NamaPasangan[50];
    int umur;
    boolean gender,IsHidup;
    FILE* file = fopen("db/Family.txt","a");

    if (file == NULL) {
        printf("File tidak dapat dibuka");
        return;
    }

    if(tree == NULL || tree->root == NULL){
        printf("Tree Belum Ada atau Root Kosong");
        return;
    }

    NkAdd TargetNode = SearchNode(tree->root,NamaNode);
    if(TargetNode == NULL){
        printf("%c Tidak Ditemukan Pada Tree",NamaNode);
        return;
    }

    if(TargetNode->Identitas.IsHidup == 0){
        printf("%c Sudah Meninggal masa mau dikawinin",NamaNode);
        return;
    }

    if(TargetNode->Pasangan != NULL){
        printf("%s sudah memiliki pasangan",NamaNode);
        return;
    }

    printf("Masukan Nama Pasangan dari %s : ",NamaNode);
    scanf(" %[^\n]",NamaPasangan);
    printf("Masukan Usia Pasangan %s : ",NamaNode);
    scanf("%d",&umur);
    if (umur > 110) {
        IsHidup = 0;
    } else {
        IsHidup = 1;
    }
    
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
    system("cls");
    printFromFile("assets/Rumah.txt");
    printf("Pasangan berhasil ditambahkan dan berkeluarga");

    if (file != NULL) {
        fprintf(file, " -> %s, %d, %d", pasangan->Identitas.info,pasangan->Identitas.Usia,pasangan->Identitas.Gender);
    }
    fclose(file);
}

void InsertMember(NTree* tree, char* parentName) {
    char namaAnak[50];
    int umur,tempGender;
    boolean gender,IsHidup = 1;
    FILE* file = fopen("db/Family.txt", "a");

    if (file == NULL) {
        printf("File tidak dapat dibuka");
        return;
    }

    if(IsEmptyTree(tree)){
        printf("Root Belum Ada");
        return;
    }

    printf("Masukan Nama Anak dari %s yang Akan Dimasukan : ",parentName);
    scanf(" %[^\n]",namaAnak);
    printf("Masukan Usia %s : ",namaAnak);
    scanf("%d",&umur);
    printf("Pilih Gender %s (0 = Perempuan, 1 = Laki-laki) : ");
    scanf("%d",&tempGender);
    if(tempGender == 0){
        gender = 0;
    }else{
        gender = 1;
    }

    AddChild(tree,parentName,namaAnak,umur,gender,IsHidup);
    
    if (file != NULL) {
        fprintf(file, "\n%s, %s, %d, %d",parentName,namaAnak,umur,gender);
    }
    fclose(file);
}

void CheckKoneksiKeluarga(NTree tree) {
    Stack P1, P2;
    NkAdd NPerson1, NPerson2;
    NkAdd Connection1, Connection2;
    char nameP1[50], nameP2[50];
    int gen1 = 0, gen2 = 0;

    InitStack(&P1);
    InitStack(&P2);

    // Input nama node
    printf("Masukan nama node yang akan dibandingkan (1) : ");
    scanf(" %[^\n]", nameP1);
    NPerson1 = SearchNode(tree.root, nameP1);

    printf("Masukan nama node yang akan dibandingkan (2) : ");
    scanf(" %[^\n]", nameP2);
    NPerson2 = SearchNode(tree.root, nameP2);

    if (NPerson1 == NULL || NPerson2 == NULL) {
        printf("Salah satu node tidak ditemukan.\n");
        return;
    }

    // Pasangan langsung
    if ((NPerson1->Pasangan && NPerson1->Pasangan == NPerson2) ||
        (NPerson2->Pasangan && NPerson2->Pasangan == NPerson1)) {
        printf("\n%s dan %s adalah pasangan langsung.\n", nameP1, nameP2);
        printf("Hubungan: Pasangan\n");
        return;
    }

    // Isi stack untuk penelusuran ke leluhur
    NkAdd temp1 = NPerson1;
    NkAdd temp2 = NPerson2;

    while (temp1 != NULL) {
        Push(&P1, temp1);
        temp1 = temp1->Parents;
    }

    while (temp2 != NULL) {
        Push(&P2, temp2);
        temp2 = temp2->Parents;
    }

    NkAdd LastCommon = NULL;
    while (!IsEmptyStack(&P1) && !IsEmptyStack(&P2)) {
        Connection1 = Pop(&P1);
        Connection2 = Pop(&P2);

        if (Connection1 == Connection2) {
            LastCommon = Connection1;
        } else {
            break;
        }
    }

    // Hitung sisa untuk generasi
    while (!IsEmptyStack(&P1)) {
        Pop(&P1);
        gen1++;
    }
    while (!IsEmptyStack(&P2)) {
        Pop(&P2);
        gen2++;
    }

    // Cetak hasil
    if (LastCommon != NULL) {
        printf("\nLeluhur terdekat bersama: %s\n", LastCommon->Identitas.info);
    } else {
        printf("\nTidak ditemukan leluhur bersama.\n");
    }

    printf("Jarak generasi dari %s ke leluhur: %d\n", nameP1, gen1);
    printf("Jarak generasi dari %s ke leluhur: %d\n", nameP2, gen2);

    // Tentukan hubungan
    printf("Hubungan antara %s dan %s: ", nameP1, nameP2);
    if (gen1 == 0 && gen2 == 1) {
        printf("Orang tua dan anak.\n");
    } else if (gen1 == 1 && gen2 == 0) {
        printf("Anak dan orang tua.\n");
    } else if (gen1 == 0 && gen2 == 2) {
        printf("Kakek/nenek dan cucu.\n");
    } else if (gen1 == 2 && gen2 == 0) {
        printf("Cucu dan kakek/nenek.\n");
    } else if (gen1 == 1 && gen2 == 1) {
        printf("Saudara kandung.\n");
    } else if (gen1 == gen2) {
        printf("Sepupu atau kerabat satu generasi.\n");
    } else {
        printf("Kerabat jauh.\n");
    }
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
