//
// Created by jincl on 2021/2/27.
//

#include "../headers/Map.h"
const int BEGIN = 0;
const int WIDTH = 18; //altezza del scenario
const int LENGTH = 40; //lunghezza del scenario

#include "../headers/Locate.h"
#include "../headers/Map.h"
#include <iostream>

using namespace std;

void print_boarder(){
    for(int i = 0; i < WIDTH; i++){ //finche non tocca l'altezza(18) 
        Locate(BEGIN, i); //spostare il cursore in (0, i) perche begin = 0
        cout << "*";
    }
    for(int i = 1; i < LENGTH; i++){ //finche non tocca la lunghezza (40)
        Locate(i, BEGIN); //spostare il cursore in (i, 0), ovver la riga sopra
        cout << "=";
        Locate(i, WIDTH-1); //spostare il cursore in (i, lunghezza-1), ovver la riga sotto, -1 perche altrimenti lascia uno spazio
        cout << "=";
    }
}
