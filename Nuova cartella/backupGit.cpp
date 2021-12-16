#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <ncurses.h>
using namespace std;

#define width 50
#define height 10

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
	bool damage;
	bool scored;
	bool healed;
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
		this->damage = false;
		this->scored = false;
		this->healed = false;
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
	void updatescore(){

	}
	void updatedamage(bool newdamage){
		damage=newdamage;
	}	
	void getdamage(){
		if (damage == true){
			this->life--;
			damage=false;
		}
	}
	void updatescore(bool newscore){
		scored = newscore;
	}
	void zeroscore(){
		this->score=0;
	}
	void scoreUp(){
		if (scored==true){
			this->score+=1;
			scored=false;
		}
	}
	void updatelife(bool newlife){
		healed = newlife;
	}
	void lifeUp(){
		if (healed==true){
			this->life++;
			healed=false;
		}
	}

	char shapebullet(){
		return bull.shape;
	}
	bool getbullet(){
		return bull.flag;
	}
	void flagbullet(bool flag){
		bull.flag=flag;
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
	int num;
	int buff;

	Entity *enemies[100]; //={{Entity('m','s')}};
	//Entity score[width];
	//Entity life[width];
	Level *next;
	Level *prev;
};

typedef Level* livello;
void drawMap(WINDOW *local_win){
	wborder(local_win,'|','|','-','-','-','-','-','-');
	wrefresh(local_win);
	mvwvline(local_win,8,width-1,' ',1);
	mvwvline(local_win,8,0,' ',1);
}
void clearMonster(livello lv,WINDOW *local_win){
	for (int i = 0;i < lv->num;i++)
		mvwaddch(local_win,lv->enemies[i]->getpositiony(),lv->enemies[i]->getpositionx(),' ');
}

livello newlv(livello lv, int &newlev, const char* t){
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

	newlev++;

	return tmp;
}
livello switchlv(livello Correntlv, player &p1, int &highest_lv, WINDOW *local_win){
	
	if (p1.getnewpositionx() >= width){
		if (Correntlv->next == NULL) {
			Correntlv=newlv(Correntlv,highest_lv,&t); // if there isn't a next lv, create it
		}
		else {
			Correntlv = Correntlv->next;	  //Correntlv is changed in nextLv
		}
		if(Correntlv->prev!=NULL) clearMonster(Correntlv->prev,local_win);
		p1.updatenewposition(p1.getstartX(),p1.getflagY());
	}
	else if (p1.getnewpositionx() <= 0){
		if (Correntlv->num != 1 ){
			mvwaddch(local_win,height/2,width/2+2,'B');
			Correntlv = Correntlv->prev;	// Correntlv is changed in prevLv
			if(Correntlv->next!=NULL)
				clearMonster(Correntlv->next,local_win);
			p1.updatenewposition(p1.getendX(),p1.getflagY());	
		};
	};
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
		
		p1.flagbullet(true);
		p1.updatebullet(p1.getpositionx()+1,p1.getpositiony());}
	break;}
	}
	mvwaddch(local_win,p1.getpositiony(),p1.getpositionx(),' ');
	}

}

void updatePlayer(WINDOW *local_win,player &p1){
	if (p1.getactive()){
		//check if the new position is valided.
		if (p1.is_move_okay(local_win,p1.getnewpositionx(),p1.getnewpositiony())==true) // if the new position is not barrier,then update new position;
			p1.updateposition(p1.getnewpositionx(),p1.getnewpositiony());
		
		if (p1.getbullet()){
			mvwaddch(local_win,p1.bulletY(),p1.bulletX()-1,' '); // clear the old position of bullet
			mvwaddch(local_win,p1.bulletY(),p1.bulletX(),p1.shapebullet()); // show up the bullet
			if (!p1.is_move_okay(local_win,p1.bulletX()+1,p1.bulletY()) || p1.bulletX()>=width) {
				p1.flagbullet(false);
				mvwaddch(local_win,p1.bulletY(),p1.bulletX(),' ');
			}
			p1.updatebullet(p1.bulletX()+1,p1.bulletY());
		}
		mvwaddch(local_win,p1.getpositiony(),p1.getpositionx(),p1.gettext());
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

	UpdateMonsterPosition(local_win,monster,dt);

	if (monster.is_move_okay(local_win,monster.getnewpositionx(),monster.getnewpositiony()))
		monster.updateposition(monster.getnewpositionx(),monster.getnewpositiony());

	mvwaddch(local_win,monster.getpositiony(),monster.getpositionx(),monster.gettext());
}

void updateScreen(WINDOW *local_win,livello lv, player &p1,float dt){
	dt/=1000.0f;
	updatePlayer(local_win,p1);
	for (int i = 0; i<lv->num;i++) updateMonster(local_win,*(lv->enemies[i]),dt);
	napms(20);
	wrefresh(local_win);
}

int main(){
	clock_t NowTime,LastTime,deltaTime;
	LastTime = clock();
	srand(time(0));
	int ch;
	WINDOW *view;
	WINDOW *scoretable;
	player p1=player('p','P');

	livello Correntlv = NULL;
	

	int highest_lv = 1;
	

	Correntlv=newlv(Correntlv,highest_lv,&t);

	initscr();
	noecho();
	cbreak();

	view=newwin(height,width,0,0);
	scoretable=newwin(height,width/2,0,width+11);

	keypad(view,TRUE);
	
	drawMap(view);
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
	}
	endwin();
	return (0);
}