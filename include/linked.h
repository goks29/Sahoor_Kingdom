#ifndef linked_h
#define linked_h
#include "BOOLEAN.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALE 1
#define FEMALE 0

/*TIPE DATA*/

typedef const char* infotype;
typedef struct Node* NkAdd;
typedef struct Partner* PartAdd;

/*INFO*/
typedef struct Info_Orang{
    char info[50];
    int Usia;
    boolean Gender;
    boolean IsHidup;
}Info;

typedef struct Partner {
    Info Identitas;
    NkAdd FirstSon;
    NkAdd NextBrother;
    NkAdd Parents;
}NkPartner;

/*NODE*/
typedef struct Node {
    Info Identitas;
    NkAdd FirstSon;
    NkAdd NextBrother;
    NkAdd Parents;
    PartAdd Pasangan;
}NodeK;


/*FUNGSI*/

NkAdd CreateNode(NkAdd parents, const char* name, int usia, boolean gender, boolean hidup);

PartAdd CreateNPartner (const char* name, int usia, boolean gender, boolean hidup);

#endif