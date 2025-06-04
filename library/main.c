#include <stdio.h>
#include <stdlib.h>
#include "Keluarga.h" // pastikan file header ini sesuai dan lengkap

int main() {
    NTree tree;
    
    // Inisialisasi tree kosong
    InitNbTree(&tree); // Pastikan InitTree ada dan sesuai

    int pilihan;
    char nama[50];

    do {
        printf("\n==== Menu Silsilah Keluarga ====\n");
        printf("1. Tambah Leluhur\n");
        printf("2. Tambah Pasangan\n");
        printf("3. Tambah Anak\n");
        printf("4. Cek Koneksi Keluarga\n");
        printf("5. Tambah Keluarga Pasangan\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar(); // bersihkan newline

        switch(pilihan) {
            case 1:
                InsertLeluhur(&tree);
                break;
            case 2:
                printf("Masukkan nama yang ingin diberi pasangan: ");
                scanf(" %[^\n]", nama);
                InsertPasangan(&tree, nama);
                break;
            case 3:
                printf("Masukkan nama orang tua: ");
                scanf(" %[^\n]", nama);
                InsertMember(&tree, nama);
                break;
            case 4:
                CheckHubunganKeluarga(tree);
                break;
            case 5:
                printf("Masukan nama pasangan yang ingin diisi data keluarga : ");
                scanf(" %[^\n]", nama);
                InsertKeluargaPasangan(&tree, nama);
                break;    
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
