//
// Created by jincl on 2021/3/4.
//
#include "../headers/mappa.h"
#include "../headers/bonus_and_enemy.h"
#include "../headers/personaggio.h"
#include <random>
#include "Progetto/headers/personaggio.h"


NPC :: NPC(char symbol=" ", bool is_there=true, int x=0, int y=0){
    this->symbol = symbol;
    this->is_there = is_there;
    this->x_NPC = x;
    this->y_NPC = y;
}

NPC :: setup(char symbol, bool is_there = true, int x, int y){
    this->symbol = symbol;
    this->is_there = true;
    this->x = LENGTH - 1;
    this->y = rand ( time(0) ) % WIDTH;
}

NPC :: void print(){
    Locate(this->x_NPC, this->y_NPC);
    cout << this->symbol;
}

NPC :: taken(){
    if (this->is_there) this->is_there = false;
}

NPC :: match(personaggio p){
    if (p.get_x_pos() == this->x_NPC && p.get_y_pos() == this->y_NPC) return true;
    else return false;
}

NPC :: get_symbol(){return this->symbol;}
NPC :: get_is_there(){return this->is_there;}
NPC :: get_x_NPC(){return this->x;}
NPC :: get_y_NPC(){return this->y;}

NPC :: set_symbol(char *symbol){this->symbol = symbol;}
NPC :: set_is_there(bool is_there){this->is_there = is_there;}
NPC :: set_x_NPC(int x){this->x_NPC = x;}
NPC :: set_y_NPC(int y){this->y_NPC = y;}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bonus :: bonus(char NPC=" ", bool is_there=true, int x=0, int y=0, int bonus_life=0, int bonus_points=0) : NPC(NPC, is_there, x, y){
    if (this->bonus_life >= 0 ) this->bonus_life = bonus_life;
    else this->bonus_life = 0;

    if(this->bonus_points >= 0 ) this->bonus_points = bonus_points;
    else this->bonus_points = 0;
}

bonus :: void apply_bonus(personaggio &p) {
    if (match(p)) {
        //Incremento punti
        p.set_points(p.get_points() + this->bonus_points);

        //Incremento vita. Vita massima: 100
        if (p.get_life() + this->bonus_points < 100) p.set_life(p.get_life() + this->bonus_life);
        else p.set_life(100);
    }
}

bonus :: get_bonus_life(){return this->bonus_life;}
bonus :: get_bonus_points(){return this->bonus_points;}

bonus :: set_bonus_life(int bonus_life){this->bonus_life = bonus_life;}
bonus :: set_bonus_points(int bonus_points){this->bonus_points = bonus_points;}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

enemy :: enemy(char NPC=" ", bool is_there=true, int x=0, int y=0, int enemy_life=0, int damage_life=0, int damage_points=0) : NPC(NPC, is_there, x, y){
    if(enemy_life > 0) this->enemy_life + enemy_life;
    else this->enemy_life = 0;

    if (damage_life >= 0) this->damage_life = damage_life;
    else this->damage_life = 0;

    if(damage_points >= 0) this->damage_points = damage_points;
    else this->damage_points = 0;
}

enemy :: apply_damage(personaggio &p){
    if(match(p)){
        //Decremento punti. Punteggio minimo: 0
        if(p.get_points() -this->damage_points > 0) p.set_points(p.get_points() - this->damage_points);
        else p.set_points(0);

        //Decremento vita. Vita minima: 0
        if(p.get_life() -this->damage_life > 0) p.set_life(p.get_life()- this->damage_life);
        else p.set_life(0);
        }
}

enemy :: get_enemy_life(){return this->enemy_life;}
enemy :: get_damage_life(){return this->damage_life;}
enemy :: get_points_life(){return this->damage_points;}

enemy :: set_enemy_life(int enemy_life){this->enemy_life = enemy_life;}
enemy :: set_damage_life(int damage_life){this->damege_life = damage_life;}
enemy :: set_damage_points(int damage_points){this->damage_points = damage_points;}




/*
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
 */