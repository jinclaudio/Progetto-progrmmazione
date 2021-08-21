//
// Created by jincl on 2021/8/21.
//
#pragma once
#ifndef GAME_POINTS_H
#define GAME_POINTS_H

#endif //GAME_POINTS_H

class points{
protected:
    int value;
public:
    //inizializzare con 0
    points();

    int get_value();
    void set_value(int x);
    void add_points(int x);
    void sub_points(int x);
    bool check_value();


};