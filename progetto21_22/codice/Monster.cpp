#include "Monster.h"

	Monster::Monster(char tipo,char text,int life):Entity(tipo,text){
		this->newposition = {0,0};
		this->life=life;
	}
	int Monster::getnewpositionx(){
		return newposition.x;
	}
	int Monster::getnewpositiony(){
		return newposition.y;
	}
	void Monster::updatenewposition(int x1,int y1){
		newposition.x=x1;
		newposition.y=y1;
	}
	int Monster::getlife(){
		return life;
	}

	void Monster::damaged(){
		life--;
		if (life <= 0) this->Death();
	}