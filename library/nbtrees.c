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

    printf("Mencari di node: %s\n", curNode->Identitas.Nama);

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

void PrintTreeRek(NkAdd node, int depth) {
    if (node == NULL) return;

    // Cetak indentasi
    for (int i = 0; i < depth; i++) printf("  ");

    // Cetak node utama dengan pasangan jika ada
    if (node->Pasangan) {
        printf("* %s (%d th) (%s) -> * %s (%d th) (%s)\n",
            node->Identitas.Nama,
            node->Identitas.Usia,
            node->Identitas.Gender ? "L" : "P",
            node->Pasangan->Identitas.Nama,
            node->Pasangan->Identitas.Usia,
            node->Pasangan->Identitas.Gender ? "L" : "P");
    } else {
        printf("* %s (%d th) (%s) (Belum ada pasangan)\n",
            node->Identitas.Nama,
            node->Identitas.Usia,
            node->Identitas.Gender ? "L" : "P");
    }

    // Anak-anak (rekursif)
    if (node->FirstSon) {
        for (int i = 0; i < depth; i++) printf("  ");
        printf("anak:\n");

        NkAdd child = node->FirstSon;
        while (child) {
            PrintTreeRek(child, depth + 1);  // Rekursif, anak dan pasangannya juga dicetak
            child = child->NextBrother;
        }
    }

    // Keluarga pasangan tetap sama seperti sebelumnya
    if (node->Pasangan && node->Pasangan->Parents) {
        printf("\n");
        for (int i = 0; i < depth; i++) printf("  ");
        printf("Keluarga dari pasangan '%s':\n", node->Pasangan->Identitas.Nama);

        NkAdd parents = node->Pasangan->Parents;

        if (parents && parents->Pasangan) {
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("* %s (%d th) (%s) -> * %s (%d th) (%s)\n",
                parents->Identitas.Nama,
                parents->Identitas.Usia,
                parents->Identitas.Gender ? "L" : "P",
                parents->Pasangan->Identitas.Nama,
                parents->Pasangan->Identitas.Usia,
                parents->Pasangan->Identitas.Gender ? "L" : "P");

            if (parents->FirstSon) {
                for (int i = 0; i < depth + 1; i++) printf("  ");
                printf("anak:\n");

                NkAdd child = parents->FirstSon;
                while (child) {
                    for (int i = 0; i < depth + 2; i++) printf("  ");
                    printf("* %s (%d th) (%s)\n",
                        child->Identitas.Nama,
                        child->Identitas.Usia,
                        child->Identitas.Gender ? "L" : "P");
                    child = child->NextBrother;
                }
            }
        }
    }
}



