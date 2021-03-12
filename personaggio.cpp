//
// Created by jincl on 2021/3/4.
//

#include "../headers/personaggio.h"
#include "../headers/Locate.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Progetto/headers/personaggio.h"

using namespace std;
personaggio :: personaggio(char symbol = ' ', int life=100, int points=0, int x_pos=0, int y_pos=0) {
    this->symbol = 'P';
    this->life = life;
    this->points = points;
    this->x_pos = x_pos;
    this->y_pos = y_pos;
}
void personaggio::setup(){
    this->life = 5;
    this->points = 0;
    this->x_pos = 3;
    this->y_pos = 3;
}
void personaggio:: print_s() { // stampa P nella mappa
    Locate(x_pos, y_pos);
    cout << symbol << endl << endl << endl ;
}

void personaggio::print_points() { //stampa il punteggio
    cout << "\nScore: " << score << endl;
}
void personaggio::print_life() { // stampa la vita
    cout << "Life: " << life << endl;
}

int personaggio :: get_x_pos(){return this->x_pos;}
int personaggio :: get_y_pos(){return this->y_pos;}
int personaggio :: get_points(){return this->points;}
int personaggio :: get_life(){return this->life;}

void personaggio :: set_x_pos(int x){this->x_pos = x;}
void personaggio :: set_y_pos(int y){this->y_pos = y;}
void personaggio :: set_points(int points){this->points = points;}
void personaggio :: set_life(int life){this->life = life;}

/*protected:
    char *symbol;
    int life;
    int score;
    int x_pos;
    int y_pos;

public:
    personaggio(){

    }
    void Setup() {
        this->life = 5;
        this->score = 0;
        this->x_pos = 1;//si suppone che il personaggio sia fisso nel coord x, e il nemico si muove verso il personaggio
        this->y_pos = 3;//si inizializza il personaggio nella striscia in mezzo, e la scriscia in alto corrisponde a y = 1, quella in basso corrisponde a y = 5
    }
    void print_s() {
        Locate(x_pos, y_pos);
        cout << symbol;
    }
};
*/
/*class enemy {
protected:
    int enemyX;
    int enemyY;
    char *symbol;
public:
    enemy() {
        this->enemyX = 0;
        this->enemyY = 0;
        this->symbol = "*";
    }

    void setup() {
        enemyX = 38;
        srand(time(0));
        int i = rand() % 3;//da migliorare, perche non abbiamo solo un nemico
        if (i == 0) {
            enemyY = 1;
        } else if (i == 1) {
            enemyY = 3;
        } else enemyY = 5;
    }
    void enemy::print(){
        Locate(enemyX, enemyY);
        cout << symbol;
    }

};
*/
