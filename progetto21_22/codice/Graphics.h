//
// Created by jincl on 2022/1/16.
//

#ifndef RELEASE_GRAPHICS_H
#define RELEASE_GRAPHICS_H
#include <ncurses.h>
#include "Level.h"
#define  width 50
#define  height 13
void drawBorder(WINDOW *local_win,livello lv);
void drawMap(WINDOW *local_win,livello lv);
void clearScene(WINDOW *scene);
void updateScoretable(WINDOW *local_win, Player &p1);


#endif //RELEASE_GRAPHICS_H
