#ifndef RELEASE_ENTITY_H
#define RELEASE_ENTITY_H
#include "Structs.h"
#include <ncurses.h>
class Entity {
	protected:
	Vec2 position;  
	char texture;    
	bool active;     
	char type;
	
	public:
	Entity(char tipo, char text);	
	
	void updateposition(int x0,int y0);
	int getpositionx();
	int getpositiony();
	bool getactive();
	void updateactive(bool state);
	char gettext();
	char gettype();
	void Death();  
	bool is_move_okay(WINDOW *local_win,int x, int y);
		
};


#endif //RELEASE_ENTITY_H