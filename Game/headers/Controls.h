//
// Created by jincl on 2021/8/21.
//

#ifndef GAME_CONTROLS_H
#define GAME_CONTROLS_H

#endif //GAME_CONTROLS_H
#include "character.h"
#include "points.h"
#include "map.h"

//muovere il personaggio
void move(character &hero, points &Points);

//controlla se il personaggio tocca il nemico
void hit(character &hero, points &, Map &map, int index);

//controlla se bisogna cambiare livello
void change_level(points point, Map &map, int index);