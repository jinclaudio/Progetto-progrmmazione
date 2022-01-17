#ifndef RELEASE_MONSTER_H
#define RELEASE_MONSTER_H
#include "Entity.h"

class Monster : public Entity{
	protected:
	Vec2 newposition;  
	int life;
	
	public:
	Monster(char tipo,char text,int life);
	int getnewpositionx();
	int getnewpositiony();
	void updatenewposition(int x1,int y1);
	int getlife();
	void damaged();
		
	
};
#endif //RELEASE_MONSTER_H
