//
// Created by jincl on 2022/1/16.
//

#ifndef RELEASE_LEVEL_H
#define RELEASE_LEVEL_H
#include "Player.h"
#include <math.h>
struct Level{
	int num_lev;
	int n_monster;
	int n_bonus;
	int id_map;
	int ExitDoor = rand() % 10 + 1;
	int EntrDoor = rand() % 10 + 1;
	bool tp_flag= false;
	bool Show_tp=false;
	bool DoorOpened = false;
	Entity *bonus[5]; 
	Entity *telep[2];
	Monster *monsters[10];
	Level *next;
	Level *prev;	
};
typedef Level* livello;
livello newlv(livello lv, int &newlv);
livello switchlv(livello Correntlv, Player &p1, int &highest_lv, WINDOW *local_win);
#endif //RELEASE_LEVEL_H
