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
        printf("Apakah Input Sudah Benar(1 = ya, 2 = tidak) : ");
        scanf("%d",&prosespilih);
        } while (prosespilih == 2);
    
    newRoot = CreateNode(NULL,NamaLeluhur,usia,gender,isHidup);
    tree->root = newRoot;   
    printf("Leluhur berhasil ditambahkan");
    
    if (file != NULL) {
        fprintf(file, "NULL, %s, %d, %d",newRoot->Identitas.Nama,newRoot->Identitas.Usia,newRoot->Identitas.Gender);
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

    if (file != NULL) {
        fprintf(file, " -> %s, %d, %d", pasangan->Identitas.Nama,pasangan->Identitas.Usia,pasangan->Identitas.Gender);
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
    
    if (file != NULL) {
        fprintf(file, "\n%s, %s, %d, %d",parentName,namaAnak,umur,gender);
    }
    fclose(file);
}

void InsertKeluargaPasangan (NTree* tree, char* PartnerName) {
    if(tree == NULL || tree->root == NULL){
        printf("Tree Belum Ada atau Root Kosong");
        return;
    }

    NkAdd Node = SearchNode(tree->root, PartnerName);

    if (Node == NULL) {
        printf("Node yang '%s' tidak ada dalam silsilah keluarga\n",PartnerName);
        getch();
        return;
    }

    if (Node->Pasangan == NULL) {
        printf("Node yang kamu cari belum mempunyai pasangan\n");
        getch();
        return;
    } 

    if (Node->Pasangan->Parents != NULL) {
        printf("Keluarga dari '%s' sudah tercatat!\n", Node->Pasangan);
        getch();
        return;
    }

    NkAdd NodeParents;
    char NamaParents[50];
    int usia, gender = 1, isHidup,prosespilih;

     // --------- Input Ayah (Parent dari pasangan) --------- //
    printf("\n-------Input Orang Tua---------\n");

    printf("\nMasukan nama Ayah dari '%s': ", Node->Pasangan->Identitas.Nama);
    scanf(" %[^\n]", NamaParents);
    getchar();
    printf("Masukkan usia (range tahun : %d tahun keatas): ",Node->Pasangan->Identitas.Usia + 18);
    scanf("%d", &usia);

    if (usia < Node->Pasangan->Identitas.Usia + 18) {
        printf("\nUsia harus 18 tahun lebih besar dari anak\n");
        getch();
        return;
    }
    printf("Apakah mash hidup ? (1 = Hidup, 0 = Tidak) : ");
    scanf("%d",&isHidup);
    getchar();

    NodeParents = CreateNode(NULL,NamaParents,usia,gender,isHidup);

    // --------- Input Ibu (Pasangan dari ayah) --------- //
    char NamaPasanganParents[50];
    int usiaPasangan, genderPasangan = 0, isHidupPasangan;

    printf("\nMasukan nama Ibu dari '%s': ", Node->Pasangan->Identitas.Nama);
    scanf(" %[^\n]", NamaPasanganParents);
    getchar();
    printf("Masukkan usia (range tahun : %d tahun keatas): ",Node->Pasangan->Identitas.Usia + 18);
    scanf("%d", &usiaPasangan);

    if (usiaPasangan < Node->Pasangan->Identitas.Usia + 18) {
        printf("\nUsia harus 18 tahun lebih besar dari anak\n");
        getch();
        return;
    }
    printf("Apakah mash hidup ? (1 = Hidup, 0 = Tidak) : ");
    scanf("%d",&isHidupPasangan);
    getchar();

    NkAdd PasanganParents = CreateNode(NULL, NamaPasanganParents,usiaPasangan, genderPasangan, isHidupPasangan);
    NodeParents->Pasangan = PasanganParents;
    PasanganParents->Pasangan = NodeParents;
    Node->Pasangan->Parents = NodeParents;
    NodeParents->FirstSon = Node->Pasangan;

    // --------- Input Saudara (NextBrother dari node) --------- //
    int jumlahSaudara;
    printf("\n-------Input Saudara---------\n");
    printf("\nBerapa jumlah saudara dari pasangan? (max 2) : ");
    scanf("%d",&jumlahSaudara);
    getchar();

    if (jumlahSaudara > 2) {
        printf("\nMaksimal hanya 2 !\nMenambahkan 2 saudara\n");
        jumlahSaudara = 2;
    }

    if (jumlahSaudara > 0) {
        NkAdd SaudaraTerakhir = Node->Pasangan;

        for (int i = 0; i < jumlahSaudara; i++) {
            char namaSaudara[50];
            int usiaSau, genderSau, hidupSau;
            printf("\nMasukan nama saudara ke-%d : ", i+1);
            scanf(" %[^\n]", namaSaudara);
            getchar();

            printf("Masukkan usia (range usia %d - 1 tahun) : ",SaudaraTerakhir->Identitas.Usia - 1);
            scanf("%d", &usiaSau);
            if (usiaSau > SaudaraTerakhir->Identitas.Usia - 1) {
                printf("\nUsia saudara harus dibawah umur kakak nya.\n");
                getch();
                return;
            }
            printf("Masukkan gender (1 = Pria, 0 = Wanita) : ");
            scanf("%d", &genderSau);
            getchar();

            printf("Apakah mash hidup ? (1 = Hidup, 0 = Tidak) : ");
            scanf("%d",&hidupSau);
            getchar();

            NkAdd Saudara = CreateNode(Node->Pasangan->Parents,namaSaudara,usiaSau,genderSau,hidupSau);
            SaudaraTerakhir->NextBrother = Saudara;
            SaudaraTerakhir = Saudara;
        }
    } else {
        printf("Tidak menambahkan saudara\n");
        getch();
        return;
    }

}

void CheckHubunganKeluarga(NTree tree) {
    Stack P1, P2;
    NkAdd NPerson1, NPerson2;
    NkAdd Connection1, Connection2;
    NkAdd visited[1000];
    char nameP1[50], nameP2[50];
    int gen1 = 0, gen2 = 0, visitedCount = 0;

    InitStack(&P1);
    InitStack(&P2);

    // Input nama node
    printf("Masukan nama node yang akan dibandingkan (1) : ");
    scanf(" %[^\n]", nameP1);
    NPerson1 = SearchNodeUniversal(tree.root, nameP1, visited, &visitedCount);

    visitedCount = 0;

    printf("Masukan nama node yang akan dibandingkan (2) : ");
    scanf(" %[^\n]", nameP2);
    NPerson2 = SearchNodeUniversal(tree.root, nameP2, visited, &visitedCount);

    if (NPerson1 == NULL || NPerson2 == NULL) {
        printf("Salah satu node tidak ditemukan.\n");
        getch();
        return;
    }

    // Pasangan langsung
    if ((NPerson1->Pasangan && strcmp(NPerson1->Pasangan->Identitas.Nama, nameP2) == 0) ||
        (NPerson2->Pasangan && strcmp(NPerson2->Pasangan->Identitas.Nama, nameP1) == 0)) {
        printf("\n%s dan %s adalah pasangan langsung.\n", nameP1, nameP2);
        printf("Hubungan: Pasangan\n");
        getch();
        return;
    }

    if ((NPerson1->Pasangan && NPerson1->Pasangan == NPerson2->Parents) || (NPerson1->Pasangan && NPerson1->Pasangan == NPerson2->Parents->Pasangan)) {
        printf("\n%s adalah mertua dari %s\n", nameP2, nameP1);
        getch();
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
        printf("\nLeluhur terdekat bersama: %s\n", LastCommon->Identitas.Nama);
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
    } else if ((gen1 == 1 && gen2 == 2) || (gen1 == 2 && gen2 == 1)) {
        printf("Paman/Bibi dan Keponakan.\n");
    } else if (gen1 == 2 && gen2 == 2) {
        printf("Sepupu.\n");
    } else if (gen1 == gen2) {
        printf("Sepupu jauh atau kerabat satu generasi lebih jauh.\n");
    } else {
        printf("Kerabat jauh atau beda generasi.\n");
    }
    getch();
}

void PrintSilsilah(NTree tree) {
    if (tree.root == NULL) {
        printf("Pohon kosong.\n");
    } else {
        PrintTreeRek(tree.root, 0);
    }
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


/*Prosedur file dan assets*/
void getDataFromFile(NTree* Tree) {
    FILE* file = fopen("db/Family.txt", "r");
    if (file == NULL) {
        printf("[x] File tidak dapat dibuka!\n");
        exit(1);
    }

    char namaLeluhur[50], namaPasangan[50];
    int usiaLeluhur, usiaPasangan, genderLeluhurInt, genderPasanganInt;

    // Format: NULL,NamaLeluhur,Usia,Gender -> NamaPasangan,Usia,Gender
    // Perbaikan: tambahkan spasi untuk mengabaikan kemungkinan spasi setelah koma
    int jumlahTerbaca = fscanf(file, "NULL, %[^,], %d, %d -> %[^,], %d, %d",
           namaLeluhur, &usiaLeluhur, &genderLeluhurInt,
           namaPasangan, &usiaPasangan, &genderPasanganInt);

    if (jumlahTerbaca != 6) {  // Ada 6 data yang dibaca (tidak 7)
        printf("[x] Format baris pertama tidak valid!\n");
        fclose(file);
        exit(1);
    }

    boolean genderLeluhur = (genderLeluhurInt == 1);
    boolean genderPasangan = (genderPasanganInt == 1);

    NkAdd leluhur = CreateNode(NULL, namaLeluhur, usiaLeluhur, genderLeluhur, true);
    NkAdd pasangan = CreateNode(NULL, namaPasangan, usiaPasangan, genderPasangan, true);

    leluhur->Pasangan = pasangan;
    pasangan->Pasangan = leluhur;

    Tree->root = leluhur;

    fclose(file);
}

void getFamilyFromFile(NTree* Tree) {
    FILE* file = fopen("db/Family.txt", "r");
    if (file == NULL) {
        printf("[x] File tidak dapat dibuka!\n");
        exit(1);
    }

    char line[256];
    char namaAnak[50], namaOrtu[50];
    int usia, genderInt;

    // Lewati baris pertama
    fgets(line, sizeof(line), file);

    // Format: NamaAnak, Usia, Gender, ParentName
    while (fgets(line, sizeof(line), file)) {
        // Tambahkan spasi di sscanf untuk abaikan spasi setelah koma
        int terisi = sscanf(line, " %[^,] , %d , %d , %[^\n]", namaAnak, &usia, &genderInt, namaOrtu);
        if (terisi != 4) {
            printf("[!] Format baris tidak valid: %s", line);
            continue;
        }

        boolean gender = (genderInt == 1);
        NkAdd parent = SearchNode(Tree->root, namaOrtu);
        if (parent != NULL) {
            NkAdd anakBaru = CreateNode(parent, namaAnak, usia, gender, true);
            if (parent->FirstSon == NULL) {
                parent->FirstSon = anakBaru;
            } else {
                NkAdd sibling = parent->FirstSon;
                while (sibling->NextBrother != NULL) {
                    sibling = sibling->NextBrother;
                }
                sibling->NextBrother = anakBaru;
            }
        } else {
            printf("[!] Parent '%s' tidak ditemukan dalam pohon.\n", namaOrtu);
        }
    }

    fclose(file);
}

void traverseLevel(NkAdd node, int level, boolean* adaYangDicetak) {
    if (node == NULL) return;

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

    traverseLevel(node->FirstSon, level - 1, adaYangDicetak);
    traverseLevel(node->NextBrother, level, adaYangDicetak);
}

void levelOrderTraversal(NkAdd root) {
    if (root == NULL) return;

    int currentLevel = 1;
    boolean adaYangDicetak = true;

    while (adaYangDicetak) {
        adaYangDicetak = false;
        printf("\t\tGenerasi %d:\n", currentLevel);
        traverseLevel(root, currentLevel, &adaYangDicetak);
        printf("\n");
        currentLevel++;
    }
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