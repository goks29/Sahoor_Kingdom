#include <stdio.h>
#include <stdlib.h>
#include "Keluarga.h" 

int main() {
    NTree tree;

    InitNbTree(&tree); 
    printFromFile("assets/SahoorFamily.txt");
    InsertLeluhur(&tree);
    int pilihan;
    char nama[50],NodeMati[50];

    do {
        system("cls");
        printf("\n\n                      Silsilah Keluarga : \n");
        PrintSilsilah(tree);
        printf("\n==== Menu Silsilah Keluarga ====\n");
        printf("1. Tambah Pasangan\n");
        printf("2. Tambah Anak\n");
        printf("3. Cek Koneksi Keluarga\n");
        printf("4. Waris Harta\n");
        printf("5. Tambahkan keluarga pasangan\n");
        printf("6. Print Tree\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar(); // bersihkan newline

        switch(pilihan) {
            case 1:
                system("cls");
                printf("\n");
                PrintSilsilah(tree);
                printf("\n");
                printf("Masukkan nama yang ingin diberi pasangan : ");
                scanf(" %[^\n]", nama);
                InsertPasangan(&tree, nama);
                break;
            case 2:
                system("cls");
                printf("\n");
                PrintSilsilah(tree);
                printf("\n");
                printf("Masukkan nama orang tua : ");
                scanf(" %[^\n]", nama);
                InsertMember(&tree, nama);
                break;
            case 3:
                system("cls");
                printf("\n");
                PrintSilsilah(tree);
                printf("\n");
                CheckHubunganKeluarga(tree);
                break;
            case 4:
                system("cls");
                printf("\n");
                PrintSilsilah(tree);
                printf("\n");
                printf("masukan nama node yang meninggal : ");
                scanf(" %[^\n]",NodeMati);
                WarisHarta(tree,NodeMati);
            case 5:
                system("cls");
                printf("\n");
                PrintSilsilah(tree);
                printf("\n");
                printf("Masukan nama pasangan yang ingin diisi data keluarga : ");
                scanf(" %[^\n]", nama);
                InsertKeluargaPasangan(&tree, nama);
            case 6:
                system("cls");
                printf("\n\n");
                PrintSilsilah(tree);
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
