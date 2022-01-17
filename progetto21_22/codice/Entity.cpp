#include "Entity.h"
#include <math.h>
	Entity::Entity(char tipo, char text){
		this->position.x = rand() % (width-2) + 1;
		this->position.y = rand() % (height-3) + 2;
		this->texture = text;
		this->active = true;
		this->type = tipo;

	}
	void Entity::updateposition(int x0,int y0){
		position.x=x0;
		position.y=y0;
	}
	int Entity::getpositionx(){
		return position.x;
	}
	int Entity::getpositiony(){
		return position.y;
	}
	bool Entity::getactive(){
		return active;
	}
	void Entity::updateactive(bool state){
		active = state;
	}
	char Entity::gettext(){
		return this->texture;
	}
	char Entity::gettype(){
		return this->type;
	}
	void Entity::Death() { 
		active=false;
		texture=' ';
	}
	bool Entity::is_move_okay(WINDOW *local_win,int x, int y){
	    char testch;
	    testch = mvwinch(local_win,y, x);
	   //  if ( testch!=' ')
	    if (testch== '-'|| testch=='|' || 
	    	testch=='X' || testch=='m' || 
	    	testch=='M' || testch=='t' ||
	    	testch=='K' || testch=='T' || 
	    	testch=='B' || testch=='H' ||
	    	testch=='/')
	    return false;
	    else return true;

	}
	
	
