//
// Created by jincl on 2021/2/27.
//

#include "../headers/Map.h"
const int BEGIN = 0;
const int WIDTH = 18;
const int LENGTH = 40;

#include "../headers/Locate.h"
#include "../headers/Map.h"
#include <iostream>

using namespace std;

void print_boarder(){
    for(int i = 0; i < WIDTH; i++){
        Locate(BEGIN, i);
        cout << "*";
    }
    for(int i = 1; i < LENGTH; i++){
        Locate(i, BEGIN);
        cout << "=";
        Locate(i, WIDTH-1);
        cout << "=";
    }
}