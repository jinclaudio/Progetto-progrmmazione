//
// Created by jincl on 2022/1/16.
//

#ifndef RELEASE_PHYSICS_H
#define RELEASE_PHYSICS_H

#include "Graphics.h"
#include "Level.h"
void controll(Player &p1,WINDOW *local_win,int &ch);

bool bullet_hit(Player &p1,Entity &e);
bool Player_hit(Player &p1, Entity &e);

void CheckPosition(WINDOW *local_win, Entity &e);

void updateMonster(WINDOW *local_win,Monster &monster,float dt);
void MonsterMove_type1(Monster &monster, Player &p, int direction);
void MonsterMove_type2(Monster &monster, Player &p,int direction);
void MonsterMove_type3(Monster &monster, Player &p,int direction);
void UpdateMonsterPosition(WINDOW *local_win, Monster &monster,float dt, Player &p, int level);
void updateBonus(WINDOW *local_win,Entity &bonus);
void updateEntity(WINDOW *local_win,livello lv,float dt,Player &p1);
void updatePlayer(WINDOW *local_win,Player &p1);
void Hitbox(WINDOW *local_win,livello lv, Player &p1,float dt);
void CheckDoor(WINDOW *local_win, livello lv);
void updateScreen(WINDOW *local_win,livello lv, Player &p1,float dt);

#endif //RELEASE_PHYSICS_H
