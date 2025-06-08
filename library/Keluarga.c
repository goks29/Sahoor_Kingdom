#include "Keluarga.h"

/*Prosedur Utama Keluarga*/
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
        printf("Apakah Input Sudah Benar(1 = ya, 2 = tidak) : ");
        scanf("%d",&prosespilih);
        } while (prosespilih == 2);
    
    newRoot = CreateNode(NULL,NamaLeluhur,usia,gender,isHidup);
    tree->root = newRoot;   
    printf("Leluhur berhasil ditambahkan");
    
    FILE* file = fopen("db/Family.txt","a");

    if (file == NULL) {
        printf("File tidak dapat dibuka");
        return;
    }

    if (file != NULL) {
        fprintf(file, "LELUHUR, %s, %d, %d\n",newRoot->Identitas.Nama,newRoot->Identitas.Usia,newRoot->Identitas.Gender);
    }
    fclose(file);
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
        printf("%s Tidak Ditemukan Pada Tree.\n",NamaNode);
        getch();
        return;
    }

    if(TargetNode->Identitas.IsHidup == 0){
        printf("%s Sudah Meninggal. Tidak bisa di nikahkan.\n",NamaNode);
        getch();
        return;
    }

    if(TargetNode->Pasangan != NULL){
        printf("%s Sudah memiliki pasangan.\n",NamaNode);
        getch();
        return;
    }

    printf("Masukan Nama Pasangan dari %s : ",NamaNode);
    scanf(" %[^\n]",NamaPasangan);
    printf("Masukan Usia %s : ",NamaPasangan);
    scanf("%d",&umur);
    if (umur < 19) {
        printf("Tidak bisa menikah ! Belum berumur 18 tahun.\n");
        getch();
        return;
    }
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

    NkAdd pasangan = CreateNode(NULL,NamaPasangan,umur,gender,IsHidup);
    if(pasangan == NULL){
        printf("Pasangan gagal dialokasi");
        return;
    }

    TargetNode->Pasangan = pasangan;
    pasangan->Pasangan = TargetNode;
    
    system("cls");
    printf("Pasangan berhasil ditambahkan dan berkeluarga");

    FILE* file = fopen("db/Family.txt","a");

    if (file == NULL) {
        printf("File tidak dapat dibuka");
        return;
    }

    if (file != NULL) {
        fprintf(file, "PASANGAN, %s, %s, %d, %d\n",  pasangan->Pasangan->Identitas.Nama,pasangan->Identitas.Nama,pasangan->Identitas.Usia,pasangan->Identitas.Gender);
    }
    fclose(file);
}

void InsertMember(NTree* tree, char* parentName) {
    char namaAnak[50];
    int umur,tempGender;
    boolean gender,IsHidup = 1;

    if(IsEmptyTree(tree)){
        printf("\nTree kosong. Tidak bisa menambahkan anak.\n");
        return;
    }

    NkAdd current = SearchNode(tree->root,parentName);

    if (current == NULL) {
        printf("\nParents '%s' tidak ditemukan.\n",parentName);
        getch();
        return;
    }

    if (current->Pasangan == NULL) {
        printf("\nParents '%s' belum menikah. Tidak bisa menambahkan anak.\n",parentName);
        getch();
        return;
    }

    printf("Masukan Nama Anak dari %s : ",parentName);
    scanf(" %[^\n]",namaAnak);
    int range = RangeUsiaAnak(current);
    printf("Masukan Usia %s (range usia 1 - %d tahun) : ",namaAnak,range);
    scanf("%d",&umur);
    printf("Pilih Gender %s (0 = Perempuan, 1 = Laki-laki) : ",namaAnak);
    scanf("%d",&tempGender);
    if(tempGender == 0){
        gender = 0;
    }else{
        gender = 1;
    }

    AddChild(tree, current, parentName, namaAnak, umur, gender, IsHidup);
    
    FILE* file = fopen("db/Family.txt", "a");

    if (file == NULL) {
        printf("File tidak dapat dibuka");
        return;
    }
    if (file != NULL) {
        fprintf(file, "ANAK, %s, %s, %d, %d\n",parentName,namaAnak,umur,gender);
    }
    fclose(file);
}

void InsertKeluargaPasangan(NTree* tree, char* PartnerName) {
    if (tree == NULL || tree->root == NULL) {
        printf("Tree belum ada atau root kosong.\n");
        getch();
        return;
    }

    // Cari node dengan nama PartnerName
    NkAdd visited[1000] = {0};
    int visitedCount = 0;
    NkAdd Node = SearchNodeUniversal(tree->root, PartnerName, visited, &visitedCount);
    if (Node == NULL) {
        printf("Node '%s' tidak ada dalam silsilah keluarga.\n", PartnerName);
        getch();
        return;
    }

    // Tentukan pasangan yang akan ditambahkan keluarganya
    NkAdd targetPasangan = NULL;
    if (strcmp(Node->Identitas.Nama, PartnerName) == 0) {
        targetPasangan = Node->Pasangan; // Jika Node adalah PartnerName, ambil pasangannya
    } else if (Node->Pasangan && strcmp(Node->Pasangan->Identitas.Nama, PartnerName) == 0) {
        targetPasangan = Node; // Jika Node adalah pasangan dari PartnerName, ambil Node
    }

    if (targetPasangan == NULL) {
        printf("Node '%s' belum memiliki pasangan.\n", PartnerName);
        getch();
        return;
    }

    // Periksa apakah targetPasangan sudah memiliki orang tua
    if (targetPasangan->Parents != NULL) {
        printf("Keluarga dari pasangan '%s' sudah tercatat!\n", targetPasangan->Identitas.Nama);
        getch();
        return;
    }

    // Buka file sekali di awal
    FILE* file = fopen("db/Family.txt", "a");
    if (!file) {
        printf("File tidak dapat dibuka.\n");
        getch();
        return;
    }

    // Input orang tua
    char NamaAyah[50], NamaIbu[50];
    int usiaAyah, usiaIbu, isHidupAyah, isHidupIbu;

    printf("\n-------Input Orang Tua---------\n");
    printf("Masukkan nama ayah dari '%s': ", targetPasangan->Identitas.Nama);
    scanf(" %[^\n]", NamaAyah);
    getchar();
    printf("Masukkan usia (min %d tahun): ", targetPasangan->Identitas.Usia + 18);
    scanf("%d", &usiaAyah);
    if (usiaAyah < targetPasangan->Identitas.Usia + 18) {
        printf("Usia ayah harus minimal 18 tahun lebih tua dari anak.\n");
        fclose(file);
        getch();
        return;
    }
    printf("Apakah masih hidup? (1 = Hidup, 0 = Tidak): ");
    scanf("%d", &isHidupAyah);
    getchar();

    printf("\nMasukkan nama ibu dari '%s': ", targetPasangan->Identitas.Nama);
    scanf(" %[^\n]", NamaIbu);
    getchar();
    printf("Masukkan usia (min %d tahun): ", targetPasangan->Identitas.Usia + 18);
    scanf("%d", &usiaIbu);
    if (usiaIbu < targetPasangan->Identitas.Usia + 18) {
        printf("Usia ibu harus minimal 18 tahun lebih tua dari anak.\n");
        fclose(file);
        getch();
        return;
    }
    printf("Apakah masih hidup? (1 = Hidup, 0 = Tidak): ");
    scanf("%d", &isHidupIbu);
    getchar();

    // Validasi nama unik
    visitedCount = 0;
    memset(visited, 0, sizeof(visited));
    if (SearchNodeUniversal(tree->root, NamaAyah, visited, &visitedCount) ||
        SearchNodeUniversal(tree->root, NamaIbu, visited, &visitedCount)) {
        printf("Nama ayah atau ibu sudah ada dalam silsilah.\n");
        fclose(file);
        getch();
        return;
    }

    // Buat node orang tua
    NkAdd NodeAyah = CreateNode(NULL, NamaAyah, usiaAyah, 1, isHidupAyah);
    NkAdd NodeIbu = CreateNode(NULL, NamaIbu, usiaIbu, 0, isHidupIbu);
    NodeAyah->Pasangan = NodeIbu;
    NodeIbu->Pasangan = NodeAyah;
    targetPasangan->Parents = NodeAyah;
    NodeAyah->FirstSon = targetPasangan;

    // Simpan data orang tua ke file
    fprintf(file, "KELUARGA_PASANGAN, %s, %s, %d, %d, %s, %d, %d\n",
            targetPasangan->Identitas.Nama, NodeAyah->Identitas.Nama, NodeAyah->Identitas.Usia,
            NodeAyah->Identitas.Gender, NodeIbu->Identitas.Nama, NodeIbu->Identitas.Usia,
            NodeIbu->Identitas.Gender);

    // Input saudara
    printf("\n-------Input Saudara---------\n");
    int jumlahSaudara;
    printf("Berapa jumlah saudara dari pasangan? (max 2): ");
    scanf("%d", &jumlahSaudara);
    getchar();

    if (jumlahSaudara > 2) {
        printf("Maksimal hanya 2 saudara.\n");
        jumlahSaudara = 2;
    }

    if (jumlahSaudara > 0) {
        NkAdd SaudaraTerakhir = targetPasangan;
        for (int i = 0; i < jumlahSaudara; i++) {
            char namaSaudara[50];
            int usiaSau, genderSau, hidupSau;
            printf("\nMasukkan nama saudara ke-%d: ", i + 1);
            scanf(" %[^\n]", namaSaudara);
            getchar();

            printf("Masukkan usia (max %d tahun): ", usiaAyah - 18);
            scanf("%d", &usiaSau);
            if (usiaSau > usiaAyah - 18 || usiaSau > usiaIbu - 18) {
                printf("Usia saudara harus minimal 18 tahun lebih muda dari orang tua.\n");
                fclose(file);
                getch();
                return;
            }
            printf("Masukkan gender (1 = Pria, 0 = Wanita): ");
            scanf("%d", &genderSau);
            getchar();
            printf("Apakah masih hidup? (1 = Hidup, 0 = Tidak): ");
            scanf("%d", &hidupSau);
            getchar();

            // Validasi nama saudara unik
            visitedCount = 0;
            memset(visited, 0, sizeof(visited));
            if (SearchNodeUniversal(tree->root, namaSaudara, visited, &visitedCount)) {
                printf("Nama saudara '%s' sudah ada dalam silsilah.\n", namaSaudara);
                fclose(file);
                getch();
                return;
            }

            NkAdd Saudara = CreateNode(NodeAyah, namaSaudara, usiaSau, genderSau, hidupSau);
            SaudaraTerakhir->NextBrother = Saudara;
            SaudaraTerakhir = Saudara;

            // Simpan saudara ke file
            fprintf(file, "SAUDARA_PASANGAN, %s, %s, %d, %d\n",
                    targetPasangan->Identitas.Nama, Saudara->Identitas.Nama,
                    Saudara->Identitas.Usia, Saudara->Identitas.Gender);
        }
    }

    fclose(file);
    printf("Keluarga pasangan '%s' berhasil ditambahkan.\n", targetPasangan->Identitas.Nama);
    getch();
}

void CetakHubungan(int gen1, int gen2, char* namaP1, char* namaP2, NkAdd lastCommon) {
    printf("Hubungan antara %s dan %s: ", namaP1, namaP2);
    
    if (lastCommon == NULL) {
        printf("Tidak ada hubungan keluarga langsung atau data tidak lengkap.\n");
        return;
    }

    if (gen1 == 0 && gen2 == 1) {
        printf("Orang tua (%s) dan anak (%s).\n", namaP1, namaP2);
    } else if (gen1 == 1 && gen2 == 0) {
        printf("Anak (%s) dan orang tua (%s).\n", namaP1, namaP2);
    } else if (gen1 == 0 && gen2 == 2) {
        printf("Kakek/nenek (%s) dan cucu (%s).\n", namaP1, namaP2);
    } else if (gen1 == 2 && gen2 == 0) {
        printf("Cucu (%s) dan kakek/nenek (%s).\n", namaP1, namaP2);
    } else if (gen1 == 0 && gen2 == 3) {
        printf("Kakek/nenek buyut (%s) dan cicit (%s).\n", namaP1, namaP2);
    } else if (gen1 == 3 && gen2 == 0) {
        printf("Cicit (%s) dan kakek/nenek buyut (%s).\n", namaP2, namaP1);
    } else if (gen1 == 1 && gen2 == 1) {
        printf("Saudara kandung (leluhur bersama: %s).\n", lastCommon->Identitas.Nama);
    } else if (gen1 == 1 && gen2 == 2) {
        printf("Paman/bibi (%s) dan keponakan (%s).\n", namaP1, namaP2);
    } else if (gen1 == 2 && gen2 == 1) {
        printf("Keponakan (%s) dan paman/bibi (%s).\n", namaP1, namaP2);
    } else if (gen1 == 2 && gen2 == 2) {
        printf("Sepupu pertama (leluhur bersama: %s).\n", lastCommon->Identitas.Nama);
    } else if (gen1 == 3 && gen2 == 3) {
        printf("Sepupu kedua (leluhur bersama: %s).\n", lastCommon->Identitas.Nama);
    } else if (gen1 == gen2) {
        printf("Sepupu ke-%d (leluhur bersama: %s).\n", gen1 - 1, lastCommon->Identitas.Nama);
    } else {
        printf("Kerabat jauh (jarak generasi %d dan %d, leluhur bersama: %s).\n", 
               gen1, gen2, lastCommon->Identitas.Nama);
    }
}

void CheckHubunganKeluarga(NTree tree) {
    Stack P1, P2;
    NkAdd NPerson1, NPerson2;
    NkAdd Connection1, Connection2;
    NkAdd visited[1000] = {0};
    char nameP1[50], nameP2[50];
    int gen1 = 0, gen2 = 0, visitedCount = 0;

    InitStack(&P1);
    InitStack(&P2);

    // Input nama node
    printf("Masukkan nama node yang akan dibandingkan (1): ");
    scanf(" %[^\n]", nameP1);
    NPerson1 = SearchNodeUniversal(tree.root, nameP1, visited, &visitedCount);

    visitedCount = 0;
    memset(visited, 0, sizeof(visited));

    printf("Masukkan nama node yang akan dibandingkan (2): ");
    scanf(" %[^\n]", nameP2);
    NPerson2 = SearchNodeUniversal(tree.root, nameP2, visited, &visitedCount);

    if (NPerson1 == NULL || NPerson2 == NULL) {
        printf("Salah satu node tidak ditemukan.\n");
        getch();
        return;
    }

    // Pemeriksaan hubungan langsung: Pasangan
    if ((NPerson1->Pasangan && strcmp(NPerson1->Pasangan->Identitas.Nama, nameP2) == 0) ||
        (NPerson2->Pasangan && strcmp(NPerson2->Pasangan->Identitas.Nama, nameP1) == 0)) {
        printf("\n%s dan %s adalah pasangan.\n", nameP1, nameP2);
        printf("Hubungan: Pasangan\n");
        getch();
        return;
    }

    // Pemeriksaan hubungan orang tua-anak melalui FirstSon
    if (NPerson1->FirstSon) {
        NkAdd child = NPerson1->FirstSon;
        while (child != NULL) {
            if (strcmp(child->Identitas.Nama, nameP2) == 0) {
                printf("\n%s adalah orang tua dari %s.\n", nameP1, nameP2);
                getch();
                return;
            }
            child = child->NextBrother;
        }
    }
    if (NPerson2->FirstSon) {
        NkAdd child = NPerson2->FirstSon;
        while (child != NULL) {
            if (strcmp(child->Identitas.Nama, nameP1) == 0) {
                printf("\n%s adalah orang tua dari %s.\n", nameP2, nameP1);
                getch();
                return;
            }
            child = child->NextBrother;
        }
    }

    // Pemeriksaan hubungan orang tua-anak melalui Parents
    if (NPerson1->Parents && strcmp(NPerson1->Parents->Identitas.Nama, nameP2) == 0) {
        printf("\n%s adalah orang tua dari %s.\n", nameP2, nameP1);
        getch();
        return;
    }
    if (NPerson2->Parents && strcmp(NPerson2->Parents->Identitas.Nama, nameP1) == 0) {
        printf("\n%s adalah orang tua dari %s.\n", nameP1, nameP2);
        getch();
        return;
    }

    // Pemeriksaan hubungan mertua
    if (NPerson1->Pasangan && NPerson1->Pasangan->Parents &&
        (strcmp(NPerson1->Pasangan->Parents->Identitas.Nama, nameP2) == 0 ||
         (NPerson1->Pasangan->Parents->Pasangan &&
          strcmp(NPerson1->Pasangan->Parents->Pasangan->Identitas.Nama, nameP2) == 0))) {
        printf("\n%s adalah mertua dari %s.\n", nameP2, nameP1);
        getch();
        return;
    }
    if (NPerson2->Pasangan && NPerson2->Pasangan->Parents &&
        (strcmp(NPerson2->Pasangan->Parents->Identitas.Nama, nameP1) == 0 ||
         (NPerson2->Pasangan->Parents->Pasangan &&
          strcmp(NPerson2->Pasangan->Parents->Pasangan->Identitas.Nama, nameP1) == 0))) {
        printf("\n%s adalah mertua dari %s.\n", nameP1, nameP2);
        getch();
        return;
    }

    // Pemeriksaan hubungan menantu
    if (NPerson1->FirstSon && NPerson1->FirstSon->Pasangan &&
        strcmp(NPerson1->FirstSon->Pasangan->Identitas.Nama, nameP2) == 0) {
        printf("\n%s adalah menantu dari %s.\n", nameP2, nameP1);
        getch();
        return;
    }
    if (NPerson2->FirstSon && NPerson2->FirstSon->Pasangan &&
        strcmp(NPerson2->FirstSon->Pasangan->Identitas.Nama, nameP1) == 0) {
        printf("\n%s adalah menantu dari %s.\n", nameP1, nameP2);
        getch();
        return;
    }

    // Pemeriksaan hubungan saudara ipar
    if (NPerson1->Pasangan && NPerson1->Pasangan->Parents) {
        NkAdd sibling = NPerson1->Pasangan->Parents->FirstSon;
        while (sibling != NULL) {
            if (strcmp(sibling->Identitas.Nama, nameP2) == 0) {
                printf("\n%s adalah saudara ipar dari %s.\n", nameP2, nameP1);
                getch();
                return;
            }
            sibling = sibling->NextBrother;
        }
    }
    if (NPerson2->Pasangan && NPerson2->Pasangan->Parents) {
        NkAdd sibling = NPerson2->Pasangan->Parents->FirstSon;
        while (sibling != NULL) {
            if (strcmp(sibling->Identitas.Nama, nameP1) == 0) {
                printf("\n%s adalah saudara ipar dari %s.\n", nameP1, nameP2);
                getch();
                return;
            }
            sibling = sibling->NextBrother;
        }
    }

    // Isi stack untuk penelusuran ke leluhur
    NkAdd temp1 = NPerson1;
    NkAdd temp2 = NPerson2;

    // Jika NPerson1 adalah pasangan, gunakan orang tua pasangannya
    if (NPerson1->Pasangan && NPerson1->Pasangan->Parents) {
        temp1 = NPerson1->Pasangan->Parents;
        gen1 = 1; // Menantu satu generasi di bawah orang tua pasangan
    } else if (temp1->Parents) {
        temp1 = temp1->Parents;
        gen1 = 1;
    }

    if (NPerson2->Pasangan && NPerson2->Pasangan->Parents) {
        temp2 = NPerson2->Pasangan->Parents;
        gen2 = 1;
    } else if (temp2->Parents) {
        temp2 = temp2->Parents;
        gen2 = 1;
    }

    while (temp1 != NULL) {
        Push(&P1, temp1);
        temp1 = temp1->Parents;
    }

    while (temp2 != NULL) {
        Push(&P2, temp2);
        temp2 = temp2->Parents;
    }

    // Cari leluhur bersama
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

    // Hitung jarak generasi
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
        printf("\nLeluhur terdekat bersama: %s\n", LastCommon->Identitas.Nama);
    } else {
        printf("\nTidak ditemukan leluhur bersama.\n");
    }

    printf("Jarak generasi dari %s ke leluhur: %d\n", nameP1, gen1);
    printf("Jarak generasi dari %s ke leluhur: %d\n", nameP2, gen2);
    
    CetakHubungan(gen1, gen2, nameP1, nameP2, LastCommon);
    getch();
}

void WarisHarta(NTree tree,char* parentName) {
    
    Queue queue;
    Qaddress Q;
    double pembagian;
    initQueue(&queue);
    int i,JmlSaudara,sdrLaki,sdrPerempuan;
    NkAdd nodeSaudara;

    JmlSaudara = 1;
    NkAdd TargetNode = SearchNode(tree.root,parentName);
    if(TargetNode == NULL){
        printf("Nama %s tidak ditemukan pada tree",parentName);
        return;
    }

    if(TargetNode->Pasangan != NULL && TargetNode->Pasangan->Identitas.IsHidup){
        if(TargetNode->Pasangan->Identitas.Gender == 1){
            if(TargetNode->FirstSon == NULL){  //bagian suami ketika tidak ada anak
                pembagian = 1.0/2.0;
                EnQueue(&queue,TargetNode->Pasangan,pembagian);
            }else{
                pembagian = 1.0/4.0; //bagian suami ketika ada anak
                EnQueue(&queue,TargetNode->Pasangan,pembagian);
            }
        }else{
            if(TargetNode->FirstSon == NULL){ //bagian istri ketika tidak ada anak
                pembagian = 1.0/4.0;
                EnQueue(&queue,TargetNode->Pasangan,pembagian);
            }else{  
                pembagian = 1.0/8.0; //bagian istri ketika ada anak
                EnQueue(&queue,TargetNode->Pasangan,pembagian);
            }            
        }
    }

    if(TargetNode->Parents->Pasangan != NULL && TargetNode->Parents->Pasangan->Identitas.IsHidup){
        if(TargetNode->Parents->Pasangan->Identitas.Gender == 0){
            if(TargetNode->FirstSon != NULL){ //bagian ibu(diakses sebagai pasangan parents) ketika ada anak
                pembagian = 1.0/6.0;
                EnQueue(&queue,TargetNode->Parents->Pasangan,pembagian);
            }else{
                pembagian = 1.0/3.0; //bagian ibu(diakses sebagai pasangan parents) ketika tidak ada anak;
                EnQueue(&queue,TargetNode->Parents->Pasangan,pembagian);
            }            
        }else{
            pembagian = 1.0/6.0; //bagian ayah(diakses sebagai pasangan parents) 
            EnQueue(&queue,TargetNode->Parents->Pasangan,pembagian);
        }
    }

    if(TargetNode->Parents != NULL && TargetNode->Parents->Identitas.IsHidup){
        if(TargetNode->Parents->Identitas.Gender == 0){
            if(TargetNode->FirstSon != NULL){ //bagian ibu ketika ada anak
                pembagian = 1.0/6.0;
                EnQueue(&queue,TargetNode->Parents,pembagian);
            }else{
                pembagian = 1.0/3.0; //bagian ibu ketika tidak ada anak;
                EnQueue(&queue,TargetNode->Parents,pembagian);
            }            
        }else{
            pembagian = 1.0/6.0; //bagian ayah 
            EnQueue(&queue,TargetNode->Parents,pembagian);
        }        
    }

    if(TargetNode->Parents->FirstSon != NULL && TargetNode->FirstSon == NULL){ //perhitungan pada saudara node
 
        JmlSaudara = 0;
        sdrLaki = 0;
        sdrPerempuan = 0;

        nodeSaudara = TargetNode->Parents->FirstSon;
        while(nodeSaudara != NULL){ //menghitung jumlah saudara node yang meninggal
            nodeSaudara = nodeSaudara->NextBrother;
            JmlSaudara++;
        }
        if(JmlSaudara > 1){ //perhitungan bagian apabila saudara yang meninggal lebih dari 1
            nodeSaudara = TargetNode->Parents->FirstSon;
            while(nodeSaudara != NULL){
                if(nodeSaudara->Identitas.Nama == TargetNode->Identitas.Nama && nodeSaudara->Identitas.IsHidup){
                    nodeSaudara = nodeSaudara->NextBrother;
                }else if(nodeSaudara->Identitas.Gender = 0 && nodeSaudara->Identitas.IsHidup){
                    sdrPerempuan++;
                    nodeSaudara = nodeSaudara->NextBrother;
                }else if(nodeSaudara->Identitas.IsHidup){
                    sdrLaki++;
                    nodeSaudara = nodeSaudara->NextBrother;
                }
            }
            if(sdrPerempuan == 0){
                nodeSaudara = TargetNode->Parents->FirstSon;
                pembagian = (1.0/2.0)/sdrLaki;
                while(nodeSaudara != NULL){
                    if(nodeSaudara->Identitas.Nama == TargetNode->Identitas.Nama ){
                        nodeSaudara = nodeSaudara->NextBrother;
                    }else if(nodeSaudara->Identitas.IsHidup){
                        EnQueue(&queue,nodeSaudara,pembagian);
                        nodeSaudara = nodeSaudara->NextBrother;
                    }
                }
            }else if(sdrLaki == 0){
                nodeSaudara = TargetNode->Parents->FirstSon;
                pembagian = (2.0/3.0)/sdrPerempuan;
                while(nodeSaudara != NULL){
                    if(nodeSaudara->Identitas.Nama == TargetNode->Identitas.Nama){
                        nodeSaudara = nodeSaudara->NextBrother;
                    }else if(nodeSaudara->Identitas.IsHidup){
                        EnQueue(&queue,nodeSaudara,pembagian);
                        nodeSaudara = nodeSaudara->NextBrother;
                    }
                }                
            }else{
                nodeSaudara = TargetNode->Parents->FirstSon;
                while(nodeSaudara != NULL){
                    if(nodeSaudara->Identitas.Nama == TargetNode->Identitas.Nama){
                        nodeSaudara = nodeSaudara->NextBrother;
                    }else if(nodeSaudara->Identitas.Gender = 1 && nodeSaudara->Identitas.IsHidup){
                        pembagian = (1.0/2.0)/sdrLaki;
                        EnQueue(&queue,nodeSaudara,pembagian);
                    }else if(nodeSaudara->Identitas.IsHidup){
                        pembagian = (1.0/4.0)/sdrPerempuan;
                        EnQueue(&queue,nodeSaudara,pembagian);
                    }
                }
            }
        }else{
            if(nodeSaudara->Identitas.Gender == 0 && nodeSaudara->Identitas.IsHidup){
                pembagian = 1.0/2.0;
                EnQueue(&queue,nodeSaudara,pembagian);
            }else if(nodeSaudara->Identitas.IsHidup){
                pembagian = 1.0/2.0;
                EnQueue(&queue,nodeSaudara,pembagian);
            }
        }
    }

    if(TargetNode->FirstSon != NULL){ //perhitungan pada anak node

        JmlSaudara = 0;
        sdrLaki = 0;
        sdrPerempuan = 0;

        nodeSaudara = TargetNode->FirstSon;
        while(nodeSaudara->NextBrother != NULL){ //menghitung jumlah saudara node yang meninggal
            nodeSaudara = nodeSaudara->NextBrother;
            JmlSaudara++;
        }
        if(JmlSaudara > 1){ //perhitungan bagian apabila saudara yang meninggal lebih dari 1
            nodeSaudara = TargetNode->FirstSon;
            while(nodeSaudara->NextBrother != NULL){
                if(nodeSaudara->Identitas.Nama == TargetNode->Identitas.Nama){
                    nodeSaudara = nodeSaudara->NextBrother;
                }else if(nodeSaudara->Identitas.Gender = 0 && nodeSaudara->Identitas.IsHidup){
                    sdrPerempuan++;
                    nodeSaudara = nodeSaudara->NextBrother;
                }else if(nodeSaudara->Identitas.IsHidup){
                    sdrLaki++;
                    nodeSaudara = nodeSaudara->NextBrother;
                }
            }
            if(sdrPerempuan == 0){
                nodeSaudara = TargetNode->FirstSon;
                pembagian = (1.0/2.0)/sdrLaki;
                while(nodeSaudara->NextBrother != NULL){
                    if(nodeSaudara->Identitas.Nama == TargetNode->Identitas.Nama){
                        nodeSaudara = nodeSaudara->NextBrother;
                    }else{
                        EnQueue(&queue,nodeSaudara,pembagian);
                        nodeSaudara = nodeSaudara->NextBrother;
                    }
                }
            }else if(sdrLaki == 0){
                nodeSaudara = TargetNode->FirstSon;
                pembagian = (2.0/3.0)/sdrPerempuan;
                while(nodeSaudara->NextBrother != NULL){
                    if(nodeSaudara->Identitas.Nama == TargetNode->Identitas.Nama){
                        nodeSaudara = nodeSaudara->NextBrother;
                    }else{
                        EnQueue(&queue,nodeSaudara,pembagian);
                        nodeSaudara = nodeSaudara->NextBrother;
                    }
                }                
            }else{
                nodeSaudara = TargetNode->FirstSon;
                while(nodeSaudara->NextBrother != NULL){
                    if(nodeSaudara->Identitas.Nama == TargetNode->Identitas.Nama){
                        nodeSaudara = nodeSaudara->NextBrother;
                    }else if(nodeSaudara->Identitas.Gender = 1){
                        pembagian = (1.0/2.0)/sdrLaki;
                        EnQueue(&queue,nodeSaudara,pembagian);
                    }else{
                        pembagian = (1.0/4.0)/sdrPerempuan;
                        EnQueue(&queue,nodeSaudara,pembagian);
                    }
                }
            }
        }else{
            if(nodeSaudara->Identitas.Gender == 0){
                pembagian = 1.0/2.0;
                EnQueue(&queue,nodeSaudara,pembagian);
            }else{
                pembagian = 1.0/2.0;
                EnQueue(&queue,nodeSaudara,pembagian);
            }
        }        
    }

    Q = queue.front;
    i = 1;
    while(Q != NULL){
        printf("\n\n===============================\n");
        printf("Pewaris Ke-%d adalah %s",i,Q->data->Identitas.Nama);
        printf("\nMendapat bagian sebesar %.2f dari harta mayyit",Q->bagianHarta);
        printf("\n===============================\n");    
        Q = Q->next;
        i++;
    }
}

void TimeSkip(NkAdd node, int year) {

}

void PrintSilsilah(NTree tree) {
    if (tree.root == NULL) {
        printf("Pohon kosong.\n");
    } else {
        PrintTreeRek(tree.root, 0);
    }
}

void CetakSilsilahPerGenerasi(NkAdd node, int level, boolean* adaYangDicetak, NkAdd root) {
    if (node == NULL) return;

    // Filter node yang berasal dari silsilah root
    if (!IsDescendantOf(node, root) && node != root) return;

    if (level == 1) {
        *adaYangDicetak = true;
        if (node->Pasangan == NULL) {
            printf("[%s] -> (%d) (%s) x [Belum ada pasangan]\n",
                   node->Identitas.Nama,
                   node->Identitas.Usia,
                   node->Identitas.Gender ? "L" : "P");
        } else {
            printf("[%s] -> (%d) (%s) x [%s] -> (%d) (%s)\n",
                   node->Identitas.Nama,
                   node->Identitas.Usia,
                   node->Identitas.Gender ? "L" : "P",
                   node->Pasangan->Identitas.Nama,
                   node->Pasangan->Identitas.Usia,
                   node->Pasangan->Identitas.Gender ? "L" : "P");
        }
    }

    CetakSilsilahPerGenerasi(node->FirstSon, level - 1, adaYangDicetak, root);

    // Selalu lanjut ke next brother (anak-anak dalam generasi yang sama)
    CetakSilsilahPerGenerasi(node->NextBrother, level, adaYangDicetak, root);
}


void PrintLevel(NkAdd root) {
    if (root == NULL) return;

    int currentLevel = 1;
    boolean adaYangDicetak = true;

    printf("\n\n          Silsilah Keluarga Inti  \n");

    while (adaYangDicetak) {
        adaYangDicetak = false;
        printf("\t\tGenerasi %d:\n", currentLevel);
        CetakSilsilahPerGenerasi(root, currentLevel, &adaYangDicetak, root);  // root sebagai filter
        printf("\n");
        currentLevel++;
    }
}


/*Prosedur file dan assets*/
void getDataFromFile(NTree* tree) {
    // Inisialisasi tree kosong
    tree->root = NULL;

    // Ambil semua data dari file
    getFamilyFromFile(tree);

    // Verifikasi: Jika tidak ada root (leluhur), beri peringatan
    if (tree->root == NULL) {
        printf("Data keluarga tidak ditemukan dalam file.\n");
    } else {
        printf("Data keluarga berhasil dimuat dari file.\n");
    }
}

void getFamilyFromFile(NTree* tree) {
    FILE* file = fopen("db/Family.txt", "r");
    if (!file) {
        printf("File tidak ditemukan.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char nama1[50], nama2[50], ayahName[50], ibuName[50];
        int usia1, gender1, usia2, gender2, isHidup1, isHidup2;
        int ayahAge, ayahGender, ibuAge, ibuGender;

        // LELUHUR
        if (sscanf(line, "LELUHUR, %49[^,], %d, %d, %d", nama1, &usia1, &gender1, &isHidup1) >= 3) {
            if (tree->root) {
                printf("Peringatan: Leluhur sudah ada, mengabaikan %s.\n", nama1);
                continue;
            }
            tree->root = CreateNode(NULL, nama1, usia1, gender1, isHidup1);
            continue;
        }

        // PASANGAN
        if (sscanf(line, "PASANGAN, %49[^,], %49[^,], %d, %d, %d", nama1, nama2, &usia2, &gender2, &isHidup2) >= 4) {
            NkAdd visited[1000] = {0};
            int visitedCount = 0;
            NkAdd node = SearchNodeUniversal(tree->root, nama1, visited, &visitedCount);
            if (!node) {
                printf("Peringatan: Node '%s' tidak ditemukan untuk PASANGAN.\n", nama1);
                continue;
            }
            NkAdd pasangan = CreateNode(NULL, nama2, usia2, gender2, isHidup2);
            node->Pasangan = pasangan;
            pasangan->Pasangan = node;
            continue;
        }

        // ANAK
        if (sscanf(line, "ANAK, %49[^,], %49[^,], %d, %d, %d", nama1, nama2, &usia2, &gender2, &isHidup2) >= 4) {
            NkAdd visited[1000] = {0};
            int visitedCount = 0;
            NkAdd parent = SearchNodeUniversal(tree->root, nama1, visited, &visitedCount);
            if (!parent) {
                printf("Peringatan: Parent '%s' tidak ditemukan untuk ANAK.\n", nama1);
                continue;
            }
            AddChild(tree, parent, nama1, nama2, usia2, gender2, isHidup2);
            continue;
        }

        // KELUARGA_PASANGAN
        if (sscanf(line, "KELUARGA_PASANGAN, %49[^,], %49[^,], %d, %d, %49[^,], %d, %d",
                   nama1, ayahName, &ayahAge, &ayahGender, ibuName, &ibuAge, &ibuGender) == 7) {
            NkAdd visited[1000] = {0};
            int visitedCount = 0;
            NkAdd pasangan = SearchNodeUniversal(tree->root, nama1, visited, &visitedCount);
            if (!pasangan) {
                printf("Peringatan: Pasangan '%s' tidak ditemukan untuk KELUARGA_PASANGAN.\n", nama1);
                continue;
            }
            NkAdd ayah = CreateNode(NULL, ayahName, ayahAge, ayahGender, 1);
            NkAdd ibu = CreateNode(NULL, ibuName, ibuAge, ibuGender, 1);
            ayah->Pasangan = ibu;
            ibu->Pasangan = ayah;
            pasangan->Parents = ayah;
            ayah->FirstSon = pasangan;
            continue;
        }

        // SAUDARA_PASANGAN
        if (sscanf(line, "SAUDARA_PASANGAN, %49[^,], %49[^,], %d, %d, %d", nama1, nama2, &usia2, &gender2, &isHidup2) >= 4) {
            NkAdd visited[1000] = {0};
            int visitedCount = 0;
            NkAdd pasangan = SearchNodeUniversal(tree->root, nama1, visited, &visitedCount);
            if (!pasangan || !pasangan->Parents) {
                printf("Peringatan: Pasangan '%s' atau orang tua tidak ditemukan untuk SAUDARA_PASANGAN.\n", nama1);
                continue;
            }
            NkAdd parents = pasangan->Parents;
            NkAdd saudara = CreateNode(parents, nama2, usia2, gender2, isHidup2);
            NkAdd temp = parents->FirstSon;
            if (temp == NULL) {
                parents->FirstSon = saudara;
            } else {
                while (temp->NextBrother) temp = temp->NextBrother;
                temp->NextBrother = saudara;
            }
            continue;
        }

        // Baris tidak valid
        printf("Peringatan: Baris tidak valid di file: %s", line);
    }

    fclose(file);
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

int RangeUsiaAnak (NkAdd Ortu) {
    int hasil;

    if (Ortu == NULL || Ortu->Pasangan == NULL) {
        return 0;
    }

    int UsiaOrtu = Ortu->Identitas.Usia;
    int UsiaPasanganOrtu = Ortu->Pasangan->Identitas.Usia;
    
    if (UsiaOrtu > UsiaPasanganOrtu) {
        hasil = UsiaPasanganOrtu - 18;
        return hasil;
    } else {
        hasil = UsiaOrtu - 18;
        return hasil;
    }
}

boolean IsDescendantOf(NkAdd node, NkAdd root) {
    NkAdd current = node->Parents;
    while (current != NULL) {
        if (current == root)
            return true;
        current = current->Parents;
    }
    return false;
}