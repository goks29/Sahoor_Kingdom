#include "nbtrees.h"

void InitNbTree (NTree* T) {
    T->root = NULL;
}

boolean IsEmptyTree (NTree* T){
    return (T->root == NULL);
}

void AddChild(NTree* T, NkAdd current, const char* parents, infotype name, int usia, boolean gender, boolean hidup) {
    int i = 2;

    if (IsEmptyTree(T)) {
        printf("Tree kosong. Tidak bisa menambahkan anak tanpa leluhur.\n");
        getch();
        return;
    }

    if (current == NULL) {
        printf("Parents '%s' tidak ditemukan.\n", parents);
        getch();
        return;
    }

    if (current->Pasangan == NULL) {
        printf("Parents '%s' belum menikah. Tidak bisa menambahkan anak.\n", current->Identitas.Nama);
        getch();
        return;
    }

    // Tentukan siapa ayah dan ibu berdasarkan gender
    NkAdd ayah = (current->Identitas.Gender == 1) ? current : current->Pasangan;
    NkAdd ibu = (current->Identitas.Gender == 0) ? current : current->Pasangan;

    // Validasi usia anak dibanding orang tua
    if ((ayah->Identitas.Usia - usia < 18) || (ibu->Identitas.Usia - usia < 18)) {
        printf("\nUsia anak tidak boleh lebih besar dari orang tua ! Harus 18 tahun dibawah usia orang tua.\n");
        getch();
        return;
    }

    NkAdd SudahAda = SearchNode(T->root, name);
    NkAdd newChild;

    if (SudahAda != NULL) {
        printf("\nNama sudah ada, silahkan beri nama lain.\n");
        getch();
        return;
    } else {
        newChild = CreateNode(ayah,name,usia,gender,hidup);
    }

    if (ayah->FirstSon == NULL) {
        ayah->FirstSon = newChild;
        ibu->FirstSon = newChild; 
        printf("\n%s merupakan first son dari %s dan %s\n", name, ayah->Identitas.Nama, ibu->Identitas.Nama);
    } else {
        NkAdd temp = ayah->FirstSon;
        while (temp->NextBrother != NULL) {
            temp = temp->NextBrother;
            i++;
        }
        temp->NextBrother = newChild;
        printf("\n%s merupakan anak ke-%d dari %s dan %s\n", name, i, ayah->Identitas.Nama, ibu->Identitas.Nama);
    }
}

NkAdd SearchNode (NkAdd curNode, const char* name) {
    if (curNode == NULL) {
        return NULL;
    } 

    if (strcmp(curNode->Identitas.Nama, name) == 0) {
        return curNode;
    }
    
    if (curNode->Pasangan != NULL && strcmp(curNode->Pasangan->Identitas.Nama,name) == 0) {
        return curNode->Pasangan;
    }

    NkAdd found = SearchNode(curNode->FirstSon,name);
    if (found != NULL) {
        return found;
    }

    return SearchNode(curNode->NextBrother,name);
    
}

boolean isVisited(NkAdd* visited, int count, NkAdd node) {
    for (int i = 0; i < count; i++) {
        if (visited[i] == node) return true;
    }
    return false;
}

NkAdd SearchNodeUniversal(NkAdd curNode, const char* name, NkAdd* visited, int* count) {
    if (curNode == NULL || *count >= 1000 || isVisited(visited, *count, curNode)) {
        return NULL;
    }

    visited[(*count)++] = curNode;

    // printf("Mencari di node: %s\n", curNode->Identitas.Nama);

    if (strcmp(curNode->Identitas.Nama, name) == 0) {
        return curNode;
    }

    NkAdd found = NULL;

    // 1. Pasangan
    if (curNode->Pasangan != NULL) {
        found = SearchNodeUniversal(curNode->Pasangan, name, visited, count);
        if (found) return found;
    }

    // 2. Anak (FirstSon)
    found = SearchNodeUniversal(curNode->FirstSon, name, visited, count);
    if (found) return found;

    // 3. Saudara kandung (NextBrother)
    found = SearchNodeUniversal(curNode->NextBrother, name, visited, count);
    if (found) return found;

    // 4. Orang tua
    found = SearchNodeUniversal(curNode->Parents, name, visited, count);
    if (found) return found;

    return NULL;
}

void PrintTreeRek(NkAdd node, int depth, int isLast) {
    if (node == NULL) return;

    // Buat indentasi dengan ASCII
    for (int i = 0; i < depth - 1; i++) {
        printf("|   ");
    }

    if (depth > 0) {
        printf(isLast ? "`-- " : "|-- ");
    }

    // Tampilkan info node
    printf("%s (%d th, %s) [%s]",
           node->Identitas.Nama,
           node->Identitas.Usia,
           node->Identitas.Gender ? "Laki-laki" : "Perempuan",
           node->Identitas.IsHidup ? "Hidup" : "Meninggal");

    // Tampilkan pasangan jika ada
    if (node->Pasangan != NULL) {
        printf("  <-->  %s (%d th, %s) [%s]",
               node->Pasangan->Identitas.Nama,
               node->Pasangan->Identitas.Usia,
               node->Pasangan->Identitas.Gender ? "Laki-laki" : "Perempuan",
               node->Pasangan->Identitas.IsHidup ? "Hidup" : "Meninggal");
    }

    printf("\n");

    // Hitung jumlah anak
    NkAdd child = node->FirstSon;
    int count = 0;
    NkAdd temp = child;
    while (temp) {
        count++;
        temp = temp->NextBrother;
    }

    // Tampilkan anak-anak
    int index = 0;
    while (child) {
        PrintTreeRek(child, depth + 1, index == count - 1);
        child = child->NextBrother;
        index++;
    }

    // Tampilkan keluarga pasangan
    if (node->Pasangan && node->Pasangan->Parents) {
        for (int i = 0; i < depth; i++) {
            printf("|   ");
        }
        printf("`-- Keluarga dari pasangan '%s':\n", node->Pasangan->Identitas.Nama);
        PrintTreeRek(node->Pasangan->Parents, depth + 1, 1);
    }
}








