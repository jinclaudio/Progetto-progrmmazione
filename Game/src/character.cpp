//
// Created by jincl on 2021/8/17.
//
#define OFFSET_X 15
#define OFFSET_Y 5
#include "character.h"
#include "utilities.h"
using namespace std;
character::character() {
    this->symbol = 'H';
    this->life = 5;
    this->x_pos = 3;
    this->y_pos = 3;
}

void character::print_character(){
    gotoxy(x_pos+OFFSET_X, y_pos+OFFSET_Y);
    cout << symbol;
}

int character::get_x_pos() {
    return this->x_pos;
}

int character::get_y_pos() {
    return this->y_pos;
}

void character::set_x_pos(int x) {
    this->x_pos = x;
}

void character::set_y_pos(int y) {
    this->x_pos = y;
}

int character::get_life() {
    return this->life;
}
void character::set_life(int n) {
    this->life = n;
}







