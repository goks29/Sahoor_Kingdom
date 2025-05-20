#include "Kingdom.h"

boolean IsEmpty(NTree* P) {
    return (P->root == NULL);
}

NkAdd CreateNode(NkAdd parents, infotype name, int usia, boolean gender, boolean hidup) {
    NkAdd newnode = (NkAdd)malloc(sizeof(NodeK));

    if (newnode != NULL) {
        strcpy(newnode->Identitas.info, name);
        newnode->Identitas.Usia = usia;
        newnode->Identitas.Gender = gender;
        newnode->Identitas.IsHidup = hidup;
        strcpy(newnode->Identitas.pasangan, "-");
        newnode->Parents = parents;
        newnode->FirstSon = NULL;
        newnode->NextBrother = NULL;
    }

    return newnode;
}
