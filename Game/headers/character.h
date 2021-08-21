//
// Created by jincl on 2021/8/17.
//

#ifndef GAME_HERO_H
#define GAME_HERO_H

#endif //GAME_HERO_H
#pragma once

class character{
protected:
    character(char symbol, int life, int points, int x_pos, int y_pos);

    char symbol;
    int life;
    int x_pos;
    int y_pos;
public:
    character();  //costruttore

    void print_character(); // stampa il personaggio sulla mappa



    int get_x_pos(); // ottieni la coordinata di p in x
    int get_y_pos(); // ottieni la coordinata di p in y

    void set_x_pos(int x);
    void set_y_pos(int y);
    int get_life();
    void set_life(int n);

};
