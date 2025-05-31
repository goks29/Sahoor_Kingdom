#include "linked.h"

NkAdd CreateNode(NkAdd parents, const char* name, int usia, boolean gender, boolean hidup) {
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

PartAdd CreateNPartner (const char* name, int usia, boolean gender, boolean hidup) {
    PartAdd newPartner = (PartAdd)malloc(sizeof(NkPartner));

    if (newPartner != NULL) {
        strcpy(newPartner->Identitas.info, name);
        newPartner->Identitas.Gender = gender;
        newPartner->Identitas.IsHidup = hidup;
        newPartner->Identitas.Usia = usia;
    } else {
        printf("Alokasi Gagal");
        return 0;
    }

    return newPartner;
}