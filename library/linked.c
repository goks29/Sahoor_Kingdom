#include "linked.h"

NkAdd CreateNode(NkAdd parents, infotype name, int usia, boolean gender, boolean hidup) {
    NkAdd newnode = (NkAdd)malloc(sizeof(NodeK));

    if (newnode != NULL) {
        strcpy(newnode->Identitas.info, name);
        newnode->Identitas.Usia = usia;
        newnode->Identitas.Gender = gender;
        newnode->Identitas.IsHidup = hidup;
        newnode->Pasangan = NULL;
        newnode->Parents = parents;
        newnode->FirstSon = NULL;
        newnode->NextBrother = NULL;
    }

    return newnode;
}

PartAdd CreateNPartner (infotype name, int usia, boolean gender, boolean hidup) {
    PartAdd newnode = (PartAdd)malloc(sizeof(NkPartner));

    if (newnode != NULL) {
        strcpy(newnode->Identitas.info, name);
        newnode->Identitas.Gender = gender;
        newnode->Identitas.IsHidup = hidup;
        newnode->Identitas.Usia = usia;
    } else {
        printf("Alokasi Gagal");
        return 0;
    }

    return newnode;
}