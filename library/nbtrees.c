#include "nbtrees.h"

void InitNbTree (NTree* T) {
    T->root = NULL;
}

boolean IsEmptyTree (NTree* T){
    return (T->root == NULL);
}

void AddChild (NTree* T, NkAdd current, const char* parents, infotype name, int usia, boolean gender, boolean hidup) {
    int i=2;

    if (IsEmptyTree(T)) {
        printf("Tree kosong. Tidak bisa menambahkan anak tanpa leluhur.\n");
        getch();
        return;
    } 

    if (current == NULL) {
        printf("Parents '%s' tidak ditemukan.\n");
        getch();
        return;
    }

    if (current->Pasangan == NULL) {
        printf("Parents '%s' belum menikah. Tidak bisa menambahkan anak.\n");
        getch();
        return;
    }

    int usiaParents = current->Identitas.Usia;
    int usiaPasangParents = current->Pasangan->Identitas.Usia;
    if ((usiaParents - usia < 18) || (usiaPasangParents - usia < 18)) {
        printf("\nUsia anak tidak boleh lebih besar dari orang tua ! Harus 18 tahun dibawah usia orang tua.\n");
        getch();
        return;
    }


    NkAdd newChild = CreateNode(current, name, usia, gender, hidup);
    if (current->FirstSon == NULL) {
        current->FirstSon = newChild;
        current->Pasangan->FirstSon = newChild;
        printf("%s merupakan first son dari %s dan %s\n",name,current->Identitas.Nama,current->Pasangan->Identitas.Nama);
    } else {
        NkAdd temp = current->FirstSon;
        while (temp->NextBrother != NULL) {
            temp = temp->NextBrother;
            i++;
        }
        temp->NextBrother = newChild;
        printf("%s merupakan anak ke-%d dari %s dan %s\n\n",name,i,current->Identitas.Nama,current->Pasangan->Identitas.Nama);
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
        return curNode;
    }

    NkAdd found = SearchNode(curNode->FirstSon,name);
    if (found != NULL) {
        return found;
    }

    return SearchNode(curNode->NextBrother,name);
    
}

int isVisited(NkAdd* visited, int count, NkAdd node) {
    for (int i = 0; i < count; i++) {
        if (visited[i] == node) return 1;
    }
    return 0;
}

NkAdd SearchNodeUniversal(NkAdd curNode, const char* name, NkAdd* visited, int* count) {
    if (curNode == NULL || (*count >= 1000) || isVisited(visited,*count,NULL)) {
        return NULL;
    }

    visited[(*count)++] = curNode;

    if (strcmp(curNode->Identitas.Nama,name) == 0 ) {
        return curNode;
    }

    NkAdd found = NULL;

    
    found = SearchNodeUniversal(curNode->Pasangan,name,visited,count);
    if (found) {
        return found;
    }

    found = SearchNodeUniversal(curNode->FirstSon,name,visited,count);
    if (found) {
        return found;
    }

    found = SearchNodeUniversal(curNode->NextBrother,name,visited,count);
    if (found) {
        return found;
    }
    
    found = SearchNodeUniversal(curNode->Parents,name,visited,count);
    if (found) {
        return found;
    }

    return NULL;
}

void PrintTreeRek(NkAdd node, int depth) {
    if (node == NULL) return;

    // Cetak indentasi
    for (int i = 0; i < depth; i++) printf("  ");

    // Cetak node utama
    printf("%s (%d th) [%s, %s]\n",
        node->Identitas.Nama,
        node->Identitas.Usia,
        node->Identitas.Gender ? "Pria" : "Wanita",
        node->Identitas.IsHidup ? "Hidup" : "Meninggal");

    // Pasangan
    if (node->Pasangan) {
        for (int i = 0; i < depth + 1; i++) printf("  ");
        printf("~ Pasangan: %s (%d th) [%s, %s]\n",
            node->Pasangan->Identitas.Nama,
            node->Pasangan->Identitas.Usia,
            node->Pasangan->Identitas.Gender ? "Pria" : "Wanita",
            node->Pasangan->Identitas.IsHidup ? "Hidup" : "Meninggal");
    }

    // Anak-anak
    if (node->FirstSon) {
        NkAdd child = node->FirstSon;
        while (child) {
            PrintTreeRek(child, depth + 2);
            child = child->NextBrother;
        }
    }

    //cetak keluarga dari pasangan
    if (node->Pasangan && node->Pasangan->Parents) {
        printf("\n");
        for (int i = 0; i < depth + 1; i++) printf("  ");
        printf("Keluarga dari pasangan '%s':\n", node->Pasangan->Identitas.Nama);
        PrintTreeRek(node->Pasangan->Parents, depth + 2);
    }
}
