//
// Created by jincl on 2021/8/21.
//

#include "points.h"

points::points() {
    this->value = 0;
}
int points::get_value() {
    return this->value;
}

void points::set_value(int x) {
    this->value = x;
}
void points::add_points(int x) {
    this->value = this->value + x;
}

void points::sub_points(int x) {
    this->value = this->value - x;
}
bool points::check_value() {
    if (value > 0){
        return  true;
    }
    else{
        return false;
    }
}
