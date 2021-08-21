//
// Created by jincl on 2021/8/21.
//

#include "Controls.h"
#include <conio.h>
#include <Windows.h>
#define MOVE 1
#define BOARDER_LEFT 1
#define BOARDER_RIGHT 99
#define BOARDER_UP 1
#define BOARDER_DOWN 48

void move(character &hero, points &point){
    char key = ' ';
    //controlla se viene premuto un tasto
    if (_kbhit()){
        key = _getch();
    }
    switch (key){
        case 'a':
            if (hero.get_x_pos()  > BOARDER_LEFT){
                hero.set_x_pos(hero.get_x_pos()-MOVE);
            }
            break;
        case 'd':
            if (hero.get_x_pos() < BOARDER_RIGHT){
                hero.set_x_pos(hero.get_x_pos()+MOVE);
            }
            break;
        case 'w':
            if (hero.get_y_pos() > BOARDER_UP){
                hero.set_y_pos(hero.get_y_pos()-MOVE);
            }
            break;
        case 's':
            if (hero.get_y_pos() < BOARDER_DOWN){
                hero.set_y_pos(hero.get_y_pos() + MOVE);
            }
            break;
    }
}

void hit(character &hero, points &point, Map map, int index) {
    pSegment tmp = new Segment;
    tmp = map.get_current_segment();
    int r = index % LENGTH;
    int x = hero.get_x_pos();
    char key = tmp->canvas[x][r];
    //controlla se nel segmento corrente c'è un elemetno in posizione (r,x)
    if (key != ' ') {
        system("CLS");
        switch (key) {
            case 'N':
                hero.set_life(hero.get_life() - 1);
                break;
            case 'X':
                point.sub_points(20);
                hero.set_life(hero.get_life() - 1);
                break;
            case 'B': //bonus
                hero.set_life(hero.get_life() + 1);
                break;
        }
    }
}

void change_level(points point, Map map, int index){
    int r = index % LENGTH;
    if ( r == 30){
        int score = point.get_value();
        //l è il nuovo livello
        int l = (score/100) + 1;
        //se l è maggiore della difficoltà corrente, allora si aumenta il livello
        if (l > map.get_current_difficulty()){
            while (l > map.get_current_difficulty()){
                map.level_up();
            }
        }
        //se l è miniore della difficoltà corrente, allora il livello di diminuisce
        else{
            while (l < map.get_current_difficulty()){
                map.level_down();
            }

        }
    }
}