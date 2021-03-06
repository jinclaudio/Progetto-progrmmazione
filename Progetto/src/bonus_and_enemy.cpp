//
// Created by jincl on 2021/3/4.
//
#include "../headers/mappa.h"
#include "../headers/bonus_and_enemy.h"
#include "../headers/personaggio.h"
bonus_and_enemy::bonus_and_enemy() {
    this->enemy = "E";
    this->damage = 1;
    this->x_en = 40;
    this->y_en = 3;
    this->bonus = 1;

}

int bonus_and_enemy::get_bonus(){
    personaggio p;

    if (p.get_x_pos()== x_bo && p.get_y_pos() == y_bo ){
        return p.get_score() + 1;
    }
}