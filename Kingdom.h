#ifndef Kingdom_h
#define Kingdom_h
#include "BOOLEAN.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALE 1
#define FEMALE 0

/*TIPE DATA*/

typedef char infotype[50];
typedef NodeK* NkAdd;

// Info
typedef struct Info_Orang{
    infotype info;
    int Usia;
    boolean Gender;
    infotype pasangan;
    boolean IsHidup;
}Info;

// Node
typedef struct Node {
    Info Identitas;
    NkAdd FirstSon;
    NkAdd NextBrother;
    NkAdd Parents;
}NodeK;

typedef struct nKTree {
    NkAdd root;
}NTree;

// Struktur List (untuk Stack & Queue)
typedef struct {
	  NkAdd Front;
	  NkAdd Rear;
	  NkAdd Top;
	  NkAdd Head;
} List;

// Queue
typedef List Queue;

// Stack
typedef List Stack;


// Fungsi

boolean IsEmpty(NTree* P);

NkAdd CreateNode(NkAdd parents, infotype name, int usia, boolean gender, boolean hidup);




#endif