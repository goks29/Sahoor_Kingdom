#include <stdio.h>
#include "nbtrees.h"

int main() {
    NTree silsilah;
    InitNbTree(&silsilah);

    AddChild(&silsilah, "", "Budi", 60, MALE, true);
    silsilah.root->Pasangan = CreateNPartner("Ani", 58, FEMALE, true);

    AddChild(&silsilah, "Budi", "Rina", 35, FEMALE, true);
    AddChild(&silsilah, "Budi", "Dika", 32, MALE, true);

    NkAdd dika = SearchNode(silsilah.root, "Dika");
    if (dika != NULL) {
        dika->Pasangan = CreateNPartner("Sari", 30, FEMALE, true);
    }

    AddChild(&silsilah, "Dika", "Nino", 10, MALE, true);

    PrintTree(silsilah);
    return 0;
}
