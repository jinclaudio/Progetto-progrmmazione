#include <iostream>

#include "headers/personaggio.h"
#include "headers/mappa.h"

using namespace std;

int main() {
    personaggio p;


    mappa m;
    m.print_boarders();
    p.Setup();
    p.print_s();

    p.print_score();
    p.print_life();

    return 0;
}
