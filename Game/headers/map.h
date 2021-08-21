#pragma once
#ifndef GAME_MAP_H
#define GAME_MAP_H

#endif //GAME_GRAPHICS_H
#include <iostream> 
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"
using namespace std;

#define LENGTH 100
#define WIDTH 50

struct Segment
{
    //una schermata, array bidimensionale
    char canvas[LENGTH][WIDTH];
    Segment *prev;
    Segment *next;
};

typedef Segment* pSegment;

struct Level{
    //difficoltà
    int difficulty;
    //primo livello
    pSegment segment;
    //prossimo livello
    Level *next;
    //livello precedente
    Level *prev;
};

typedef Level* pLevel;

class Map{
protected:
    //difficolta del livello corrente
    int current_difficulty;
    //segmento corrente, successivo e precedente
    pSegment segment_current, segment_next, segment_prev;
    //nemici nel livello
    pLevel level;
public:
    //costruttore
    Map();
    //ritorna difficolta corrente
    int get_current_difficulty();
    //ritorna segmento corrente
    pSegment get_current_segment();
    //prossimio
    pSegment get_next_segment();
    //precedente
    pSegment get_prev_segment();
    //ritorna il livello
    pLevel get_current_level();
    //crea un nuovo livello
    void new_level();
    //crea un nuovo segmento quando si arriva all'ultimo
    void new_segment(int difficulty);
    //sostituisce il segmento corrente con il prossimo
    void shift(int x);
    //controlla se è l'ultimo segmento
    void last(int x);
    //aumenta livello
    void level_up();
    //diminuire livello
    void level_down();
    //stampare i bordi
    void print(int x);


};
