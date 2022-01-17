#include "Player.h"

	Player::Player(char tipo, char text, int life) : Monster(tipo, text, life), bull(bull) {
		this->position.x = 1;
		this->position.y = height-2; // 数字越低， 显示的地方越低
		this->score=0;
		this->count = 0;
        this->bull = Entity('b', '>');

	}

	
	int Player::getscore(){
		return score;
		}
    void Player::damaged(int n){
        this->life -= n;
        if (this->life <= 0)
            this->Death();
    }
	void Player::scored(){
		score +=10;
		}
	void Player::lifeUP(){
		life++;
		}
	
	bool Player::bulletFlag(){
		return bull.getactive();
		}
	void Player::updateFlag(bool flag){
		bull.updateactive(flag);
		}
	char Player::shapebullet(){
		return bull.gettext();
		}
	bool Player::getbullet(){
		return bull.getactive();
		}
	
	void Player::updatebullet(int x,int y){
        bull.updateposition(x,y);

		}
	int Player::bulletX(){
		return bull.getpositionx();
		}
	int Player::bulletY(){
		return bull.getpositiony();
		}

void Player::conta() {
    count ++;
}

int Player::getCount() {
    return this->count;
}
