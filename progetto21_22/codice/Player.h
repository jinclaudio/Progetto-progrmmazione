#ifndef RELEASE_PLAYER_H
#define RELEASE_PLAYER_H
#include "Monster.h"
class Player : public Monster{
	protected:
	int score;
    int count;
	Entity bull;
	public:
	Player(char tipo, char text, int life);
	int getscore();
	void scored();
	void lifeUP();
    void damaged(int n);
	bool bulletFlag();
	void updateFlag(bool flag);
	char shapebullet();
	bool getbullet();
	void updatebullet(int x,int y);
	int bulletX();
	int bulletY();
    void conta();
    int getCount();
};
#endif //RELEASE_PLAYER_H
