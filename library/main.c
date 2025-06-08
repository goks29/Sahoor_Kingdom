#include <stdio.h>
#include <stdlib.h>
#include "Keluarga.h" 

int main() {
    NTree tree;

    InitNbTree(&tree); 

    int pilihan;
    char nama[50],NodeMati[50];
    system("cls");
	
    getDataFromFile(&tree);
    
    if(IsEmptyTree(&tree)){
		InsertLeluhur(&tree);	
	}
	

    do {
        system("cls");
        printf("\n==========================================================\n");
        printf("               KEADAAN KELUARGA SAHOOR\n");
        printf("==========================================================\n");
        if (IsEmptyTree(&tree)) {
            printf("[!] Pohon keluarga kosong.\n");
        } else {
            PrintLevel(tree.root);
        }
        printf("\n");
        printf("\n==== Menu Silsilah Keluarga ====\n");
        printf("1. Tambah Pasangan\n");
        printf("2. Tambah Anak\n");
        printf("3. Cek Hubungan Keluarga\n");
        printf("4. Waris Harta\n");
        printf("5. Tambahkan keluarga pasangan\n");
        printf("6. Print Tree\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar();

        switch(pilihan) {
            case 1:
                system("cls");
                printf("\n=======================================\n");
                printf("\n            TAMBAH PASANGAN            \n");
                printf("\n=======================================\n");
                printf("\n");
                PrintLevel(tree.root);
                printf("\n");
                printf("Masukkan nama yang ingin diberi pasangan : ");
                scanf(" %[^\n]", nama);
                InsertPasangan(&tree, nama);

                printf("\n\n");
                system("Pause");
                break;
            case 2:
                system("cls");
                printf("\n=======================================\n");
                printf("\n              TAMBAH ANAK              \n");
                printf("\n=======================================\n");
                printf("\n");
                PrintLevel(tree.root);
                printf("\n");
                printf("Masukkan nama orang tua : ");
                scanf(" %[^\n]", nama);
                InsertMember(&tree, nama);

                printf("\n\n");
                system("Pause");
                break;
            case 3:
                system("cls");
                printFromFile("Assets/CekAnggota.txt");
                printf("\n==========================================================\n");
                printf("\n                CEK HUBUNGAN ANGGOTA KELUARGA\n");
                printf("\n==========================================================\n");
                printf("\n");
                PrintSilsilah(tree);
                printf("\n");
                CheckHubunganKeluarga(tree);

                printf("\n\n");
                system("Pause");
                break;

            case 4:
                system("cls");
                printFromFile("assets/PenerusHarta.txt");
                printf("\n                              ===============================================================\n");
                printf("\n                                                        PENERUS HARTA\n");
                printf("\n                              ===============================================================\n");

                PrintLevel(tree.root);
                printf("\n");
                printf("masukan nama node yang meninggal : ");
                scanf(" %[^\n]",NodeMati);
                WarisHarta(tree,NodeMati);

                printf("\n\n");
                system("Pause");
                break;

            case 5:
                system("cls");
                printf("\n");
                PrintLevel(tree.root);
                printf("\n");
                printf("Masukan nama pasangan yang ingin diisi data keluarga : ");
                scanf(" %[^\n]", nama);
                InsertKeluargaPasangan(&tree, nama);

            case 6:
                system("cls");
                printf("\n\n");
                PrintSilsilah(tree);
                printf("\nKetik apapun untuk melanjutkan.\n");
                getch();
            case 0:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    } while (pilihan != 0);

    return 0;
}