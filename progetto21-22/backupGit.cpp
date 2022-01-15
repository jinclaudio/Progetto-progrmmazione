#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <ncurses.h>
using namespace std;

#define width 50
#define height 13

struct Vec2 {
	float x;
	float y;
};
struct bullet{
	bool flag;
	float x;
	float y;
	char shape;
	int num;
};

class Entity {
	protected:
	Vec2 position;  //位置
	Vec2 newposition;  //新位置
	char texture;    //纹理（要显示的图形）
	bool active;     //是否存活
	char type;
	public:
	Entity(char tipo, char text){
		this->position.x = rand() % (width-2) + 2;
		this->position.y = rand() % (height-3) + 2;
		this->newposition = {0,0};
		this->texture = text;
		this->active = true;
		this->type = tipo;
	}
	Vec2 getpostion(){
		return position;
	}

	void updateposition(float x0,float y0){
		position.x=x0;
		position.y=y0;
	}

	void updatenewposition(float x1,float y1){
		newposition.x=x1;
		newposition.y=y1;
	}
	float getpositionx(){
		return position.x;
	}
	float getpositiony(){
		return position.y;
	}
	float getnewpositionx(){
		return newposition.x;
	}
	float getnewpositiony(){
		return newposition.y;
	}
	
	bool getactive(){
		return active;
	}
	void updateactive(bool state){
		active = state;
	}
	char gettext(){
		return this->texture;
	}
	char gettype(){
		return this->type;
	}
	void Death() { 
		this->updateactive(false);
		texture=' ';
	}

	bool is_move_okay(WINDOW *local_win,float x, float y){
	    char testch;
	    testch = mvwinch(local_win,y, x);
	    if (testch == '-' || testch == '|') return false;
	    else return true;
	}
};
class player : public Entity{
	protected:
	int life;
	int score;
	float startX;
	float endX;
	float flagY;
	bullet bull;
	public:
	player(char tipo,char text):Entity(tipo,text){
		this->position.x = 1;
		this->position.y = height-2; // 数字越低， 显示的地方越低
		this->life=3;
		this->score=0;
		this->startX = 1;
		this->endX = width-2;
		this->flagY = height-2;
		this->bull={false,0,0,'>'};
	}
	float getflagY(){
		return flagY;
	}
	float getstartX(){
		return startX;
	}
	float getendX(){
		return endX;
	}
	int getlife(){
		return life;
	}
	void updatelife(int newlife){
		this->life = newlife;
	}
	int getscore(){
		return score;
	}

	void scored(){
		score +=10;
	}

	void damaged(){
		if (this->life>0) life--;
		else this->Death();
	}
	
	/*void updatelife(bool newlife){
		healed = newlife;
	}
	void lifeUp(){
		if (healed==true){
			this->life++;
			healed=false;
		}
	}*/
	bool bulletFlag(){
		return bull.flag;
	}
	void updateFlag(bool flag){
		bull.flag=flag;
	}
	char shapebullet(){
		return bull.shape;
	}
	bool getbullet(){
		return bull.flag;
	}
	
	void updatebullet(float x,float y){
		bull.x=x;
		bull.y=y;
	}
	float bulletX(){
		return bull.x;
	}
	float bulletY(){
		return bull.y;
	}
};


struct Level{
	int n_monster;
	int n_bonus;
	int n_artefatti

	Entity *enemies[100]; //={{Entity('m','s')}};
	//Entity score[width];
	//Entity life[width];
	Level *next;
	Level *prev;
	int id_map;
};

typedef Level* livello;

void rectangle(WINDOW *local_win, int x, int y, int long1, int long2){
	mvwhline(local_win, y, x, '-', long1+1);
	mvwhline(local_win, y+long2-1, x, '-', long1+1);
	mvwvline(local_win, y, x, '|', long2);
	mvwvline(local_win, y, x+long1+1, '|', long2);	
}

void drawScene(WINDOW *local_win,int id){
	switch(id){
		case 1:{
				mvwhline(local_win,  6,  1,  '-', 46);
			for (int i = 7;i < 45; i = i+8)
				mvwvline(local_win, 3, i, '|', 3);

			for (int i = 3; i < 45; i = i+8)
				mvwvline(local_win, 7, i, '|', 3);

			for (int i = 3; i < 50; i = i+8)
				mvwvline(local_win, 1, i, '|', 3);

			for (int i = 7; i < 45; i = i+8)
				mvwvline(local_win, 9, i, '|', 3);

			mvwvline(local_win, 4, 0, ' ', 2);
			mvwvline(local_win, 8, 0, 'X', 2);
		}
		break;
		case 2:{
			mvwhline(local_win,  6,  1,  '-', 48);
			for (int i = 10; i < 50; i = i+10)
				mvwvline(local_win, 1, i, '|', 11);
			mvwvline(local_win,  8,  0,  ' ', 2);
			mvwhline(local_win,  12,  45,  'X', 2);
		}
		break;
		case 3:{
			mvwhline(local_win,  4,  1,  '-', 8);
			mvwhline(local_win,  8,  39,  '-', 8);
			mvwvline(local_win, 5, 4, '|', 3);
			mvwvline(local_win, 1, 19, '|', 7);
			mvwvline(local_win, 9, 24, '|', 3);
			mvwhline(local_win,  5,  20,  '-', 10);
			mvwvline(local_win, 1, 38, '|', 9);
			mvwvline(local_win, 9, 0, ' ', 2);
			mvwvline(local_win, 1, 49, 'X', 2);
		}

		break;
		case 4:{
			 rectangle(local_win, 3, 3, 42, 7);
			 mvwhline(local_win, 6, 6, '-', 38);
			 mvwhline(local_win, 12, 5, ' ', 2);
			 mvwhline(local_win, 12, 46, 'X', 2);
		}
		break;
		case 0:{
			mvwhline(local_win,5,20,'-',5);
			//id default 0 for test, when is done, change the id in newlv().
		}
		break;
		case 100:{
			mvwvline(local_win,5,20,'|',5);
			//id default 0 for test, when is done, change the id in newlv().
		}
		break;
	}
}

void drawMap(WINDOW *scene,WINDOW *scoretable){

	box(scoretable, '|', '*');
	wborder(scene,'|','|','-','-','-','-','-','-');
	mvwvline(scene,8,width-1,' ',1);
	mvwvline(scene,8,0,' ',1);
}

void updateScoretable(WINDOW *local_win, player &p1,int id){

	mvwprintw(local_win,1,3,"Life: %d", p1.getlife());
	mvwprintw(local_win,2,3,"Score: %d",p1.getscore());
	mvwprintw(local_win,3,3,"id_map: %d",id);
	wrefresh(local_win);

}
void clearMonster(WINDOW *local_win, Entity &monster){
	mvwaddch(local_win,monster.getpositiony(),monster.getpositionx(),' ');
}
void clearScene(WINDOW *scene){
	for(int y = 1;y<height-1;y++)
		mvwhline(scene,y,1,' ',width-2);
}

livello newlv(livello lv, int &newlev){
		livello tmp;
		tmp = new Level;
	//set lv;
		tmp->num=newlev;

	//init. monster,buff
		if (newlev < 5)			 // there is only 1 buff when the lv is under 5
			tmp->buff = 1;
		else tmp->buff = newlev-4; 	

		//for (int i = 0; i < 5; i ++){
		for (int i = 0; i < newlev; i ++){
			tmp->enemies[i]= new Entity('m','#');
			//tmp->score[i]=Entity('s','$');
		}

		for (int i = 0; i < tmp->buff; i ++){
			//tmp->life[i]=Entity('l','O');
		}
	tmp->prev = lv;
	tmp->next = NULL;

	if (lv != NULL) lv->next = tmp;

	//tmp->id_map = rand() % 4 +1;
	if (newlev%2 == 0)
		tmp->id_map=0;
	else tmp->id_map=100;

	newlev++;

	return tmp;
}

livello switchlv(livello Correntlv, player &p1, int &highest_lv, WINDOW *local_win){
	
	if (p1.getnewpositionx() >= width){
		if (Correntlv->next == NULL) {
				Correntlv=newlv(Correntlv,highest_lv); // if there isn't a next lv, create it
			}
			else
			{Correntlv = Correntlv->next;	  //Correntlv is changed in nextLv
		}
		p1.updatenewposition(p1.getstartX(),p1.getflagY());
	}
	else if (p1.getnewpositionx() <= 0){
		if (Correntlv->num != 1 ){
			mvwaddch(local_win,height/2,width/2+2,'B');
			Correntlv = Correntlv->prev;	// Correntlv is changed in prevLv
				
			

			p1.updatenewposition(p1.getendX(),p1.getflagY());	
		};
	};
	clearScene(local_win);
	return Correntlv;
}

void controll(player &p1,WINDOW *local_win,int &ch){

	//you can controll only if the player is alive
	if (p1.getactive() == true){
	switch (ch) {
	case KEY_UP:
	case 'w':
	case 'W':	{
		p1.updatenewposition(p1.getpositionx(), p1.getpositiony()-1);
		
	    break;}

	case KEY_DOWN:
	case 's':
	case 'S':{
		p1.updatenewposition(p1.getpositionx(), p1.getpositiony()+1);
	
	    break;}

	case KEY_LEFT:
	case 'a':
	case 'A':{
		p1.updatenewposition(p1.getpositionx()-1, p1.getpositiony());
	
	    break;}
	case KEY_RIGHT:
	case 'd':
	case 'D':{
	p1.updatenewposition(p1.getpositionx()+1, p1.getpositiony());
	
	    break;}
	case ' ':
	case 'j':
	case 'J':{
		if (!p1.getbullet()){
		
		p1.updateFlag(true);
		p1.updatebullet(p1.getpositionx()+1,p1.getpositiony());}
	break;}
	}
	mvwaddch(local_win,p1.getpositiony(),p1.getpositionx(),' ');
	}
}

void updatePlayer(WINDOW *local_win,player &p1){
	//player part
		if (p1.getactive()){
			//check if the new position is valided.
			if (p1.is_move_okay(local_win,p1.getnewpositionx(),p1.getnewpositiony())) // if the new position is not barrier,then update new position;
				p1.updateposition(p1.getnewpositionx(),p1.getnewpositiony());

		mvwaddch(local_win,p1.getpositiony(),p1.getpositionx(),p1.gettext());
	
	// bullet part
		if (p1.getbullet()){
			mvwaddch(local_win,p1.bulletY(),p1.bulletX()-1,' '); // clear the old position of bullet
			mvwaddch(local_win,p1.bulletY(),p1.bulletX(),p1.shapebullet()); // show up the bullet
			
			if ((!p1.is_move_okay(local_win,p1.bulletX()+1,p1.bulletY()) || p1.bulletX()>=width) && p1.bulletFlag()) {
				p1.updateFlag(false);
				mvwaddch(local_win,p1.bulletY(),p1.bulletX(),' ');
			}
			p1.updatebullet(p1.bulletX()+1,p1.bulletY());
		}

	
	}
}

void UpdateMonsterPosition(WINDOW *local_win, Entity &monster,float dt){
	static float timeCounter = 0.0f;
	timeCounter += dt;

	if (timeCounter >= 10.0f){
		timeCounter = 0.0f;
		int direction = rand() % 4 +1;

		switch(direction){
				case 1:
					 monster.updatenewposition(monster.getpositionx(),monster.getpositiony()-1);
				break;
				case 2:
				
					 monster.updatenewposition(monster.getpositionx(),monster.getpositiony()+1);
				break;
				case 3:
				
					 monster.updatenewposition(monster.getpositionx()-1,monster.getpositiony());
				break;
				case 4:
				
					 monster.updatenewposition(monster.getpositionx()+1,monster.getpositiony());
				break;	
			}
			mvwaddch(local_win,monster.getpositiony(),monster.getpositionx(),' ');
	}
}

void updateMonster(WINDOW *local_win, Entity &monster,float dt){
	if (!monster.is_move_okay(local_win,monster.getpositionx(),monster.getpositiony())){
		while(monster.is_move_okay(local_win,monster.getpositionx(),monster.getpositiony())){
			float y1=rand() % (height-3) + 2;
			float x1=rand() % (width-2) + 2;
			monster.updateposition(x1,y1);
		};
	};

	if(monster.getactive()){

		UpdateMonsterPosition(local_win,monster,dt);

		if (monster.is_move_okay(local_win,monster.getnewpositionx(),monster.getnewpositiony()))
			monster.updateposition(monster.getnewpositionx(),monster.getnewpositiony());

		mvwaddch(local_win,monster.getpositiony(),monster.getpositionx(),monster.gettext());
	}

}
bool bullet_hit(player &p1,Entity &e){
	return((p1.bulletX() == e.getpositionx()) && 
		   (p1.bulletY() == e.getpositiony()) &&
		   (p1.bulletFlag()) &&
		   (e.getactive()));
}
bool player_hit(player &p1,Entity &e){
	return( (p1.getpositionx() == e.getpositionx()) && 
			(p1.getpositiony() == e.getpositiony()) &&
			e.getactive() );
}
void Hitbox(WINDOW *local_win,livello lv, player &p1){
	for (int i = 0; i <lv->num; i++){
		//bullet && monster
		   	if (bullet_hit(p1, *(lv->enemies[i]) ) ) {
			    
			    p1.updateFlag(false);
				mvwaddch(local_win,p1.bulletY(),p1.bulletX()-1,' ');

			    lv->enemies[i]->Death();

			    clearMonster(local_win,*(lv->enemies[i]));
			    p1.scored();
		   }

	   // player && monsterss
		   if (player_hit(p1,*(lv->enemies[i]) ) ){
			   lv->enemies[i]->Death();
			   p1.damaged();
		   }
	}
	for 
}

void updateScreen(WINDOW *local_win,livello lv, player &p1,float dt){
	dt/=1000.0f;
	drawScene(local_win,lv->id_map);
	
	updatePlayer(local_win,p1);
	for (int i = 0; i<lv->num;i++) updateMonster(local_win,*(lv->enemies[i]),dt);
	// varie for per aggiornare varie cose.

	Hitbox(local_win,lv,p1);
	napms(20);
}

int main(){
	clock_t NowTime,LastTime,deltaTime;
	LastTime = clock();
	srand(time(0));
	int ch;
	WINDOW *view,*scoretable;
	
	player p1=player('p','P');

	livello Correntlv = NULL;
	

	int highest_lv = 1;
	

	Correntlv=newlv(Correntlv,highest_lv);

	initscr();
	noecho();
	cbreak();
	
	view=newwin(height,width,0,0);
	scoretable=newwin(6,15,0,width+1);

	keypad(view,TRUE);
	
	drawMap(view,scoretable);
	//drawMap2(scoretable);
	while (ch != 'q'){
		NowTime=clock();
		deltaTime = NowTime - LastTime;
		LastTime = NowTime;

		if (nodelay(view,TRUE)!= ERR)
			ch = wgetch(view);

		controll(p1,view,ch);

		Correntlv=switchlv(Correntlv,p1,highest_lv,view);

		if (Correntlv->next != NULL) mvwaddch(view,height/2,width/2+4,'d');

		updateScreen(view,Correntlv,p1,deltaTime);
		updateScoretable(scoretable,p1,Correntlv->id_map);

		wrefresh(view);
		
	}
	endwin();
	return (0);
}