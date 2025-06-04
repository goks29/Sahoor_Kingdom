#include "linked.h"

NkAdd CreateNode(NkAdd parents, const char* name, int usia, boolean gender, boolean hidup) {
    NkAdd newnode = (NkAdd)malloc(sizeof(NodeK));

    if (newnode != NULL) {
        strcpy(newnode->Identitas.info, name);
        newnode->Identitas.Usia = usia;
        newnode->Identitas.Gender = (boolean)gender;
        if(newnode->Identitas.Usia > 110){
            newnode->Identitas.IsHidup = 0;
        }else{
            newnode->Identitas.IsHidup = 1;
        }
        newnode->Pasangan = NULL;
        newnode->Parents = parents;
        newnode->FirstSon = NULL;
        newnode->NextBrother = NULL;
    }

    return newnode;
}
