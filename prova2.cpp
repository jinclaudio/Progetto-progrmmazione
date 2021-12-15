#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <ncurses.h>
using namespace std;

#define width 50
#define height 10
const char t = '0';
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
		this->position.y = rand() % (height-2)+2;
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
		this->startX = 0;
		this->endX = width;
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
	const char *name[1];   		// used for give name to the file
	Entity *enemies[100]; //={{Entity('m','s')}};
	//Entity score[width];
	//Entity life[width];
	Level *next;
	Level *prev;
};

typedef Level* livello;

livello newlv(livello lv, int &newlev, const char* t){
	livello tmp;
	tmp = new Level;
	 
	tmp->num=newlev;

	if ( newlev==1)
		tmp->name[0] = t;			// if lv == 0, then name = t
	else
		tmp->name[0]= *(lv->name)+1;//  else name = prev.name + 1

	if (newlev < 5)			 // there is only 1 buff when the lv is under 5
		tmp->buff = 1;
	else tmp->buff = newlev-4; 	 // after lv 5, the buff number will add 1 per lv.

	for (int i = 0; i < newlev; i ++){
		tmp->enemies[i]= new Entity('m','#');
		//tmp->score[i]=Entity('s','$');
	}

	for (int i = 0; i < tmp->buff; i ++){
		//tmp->life[i]=Entity('l','O');
	}

	/*if (lv = 0)
		tmp->prev = NULL;
	else*/ 
	tmp->prev = lv;
	tmp->next = NULL;
	if (lv != NULL) lv->next = tmp;

	newlev++;

	return tmp;
}
livello switchlv(livello Correntlv, player &p1, int &highest_lv, WINDOW *local_win){
	if (p1.getpositionx() >= width){
		if (Correntlv->next == NULL) {
			Correntlv=newlv(Correntlv,highest_lv,&t); // if there isn't a next lv, create it
			
			//clear();
			//drawMap(local_win);
		}
		else {
			scr_dump(Correntlv->name[0]);	  // save the screen as a file 
			Correntlv = Correntlv->next;	  //Correntlv is changed in nextLv
			scr_restore(Correntlv->name[0]);  // restore the file as a screen
			doupdate();						// update screen
		}
		p1.updatenewposition(p1.getstartX(),p1.getflagY());
		//mvwaddch(local_win,p1.getflagY(),p1.getstartX(),p1.gettext());  //update the starting position of player
	}

	else if (p1.getpositionx() <= 0){
		if (Correntlv->num != 0 ){
			scr_dump(Correntlv->name[0]);	// save the screen as file named
			Correntlv = Correntlv->prev;	// Correntlv is changed in prevLv
			scr_restore(Correntlv->name[0]); // restore the file as a screen
			doupdate();	
			
			p1.updatenewposition(p1.getendX(),p1.getflagY());					// update screen
			//mvwaddch(local_win,p1.getflagY(),p1.getendX(),p1.gettext()); //update the starting position of player
		};
	};
	return Correntlv;
}

void drawMap(WINDOW *local_win){
	wborder(local_win,' ',' ','-','-','-','-','-','-');
	wrefresh(local_win);
}

void controll(player &p1,WINDOW *local_win,int &ch){
	bool haveMoved = false;
	
	//如果玩家死亡，则不能操作
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
	//mvwaddch(local_win,p1.bulletY(),p1.bulletX()-1, ' ');
	mvwaddch(local_win,p1.getpositiony(),p1.getpositionx(),' ');
	}

}

void updatePlayer(WINDOW *local_win,player &p1){
	if (p1.getactive()){
		//记录原实体位置
		if (p1.is_move_okay(local_win,p1.getnewpositionx(),p1.getnewpositiony())==true) // if the new position is not barrier,then update new position;
			p1.updateposition(p1.getnewpositionx(),p1.getnewpositiony());
		
		if (p1.getbullet()){
		//	for (int i = 0; i<2; i++){
			mvwaddch(local_win,p1.bulletY(),p1.bulletX()-1,' ');
			mvwaddch(local_win,p1.bulletY(),p1.bulletX(),p1.shapebullet());
			if (!p1.is_move_okay(local_win,p1.bulletX()+1,p1.bulletY())){
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
			//if (monster.is_move_okay(local_win,monster.getpositionx()-1,monster.getpositiony()))
				 monster.updatenewposition(monster.getpositionx()-1,monster.getpositiony());
			break;
			case 4:
			//	if (monster.is_move_okay(local_win,monster.getpositionx()+1,monster.getpositiony()))
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

	for (int i = 0; i<lv->num;i++)
		updateMonster(local_win,*(lv->enemies[i]),dt);

	
	napms(10);
	wrefresh(local_win);

}

int main(){
	clock_t NowTime,LastTime,deltaTime;
	LastTime = clock();
	//srand(time(0));
	int ch;
	WINDOW *view;
	player p1=player('p','P');

	livello Correntlv = NULL;
	

	int highest_lv = 1;
	

	Correntlv=newlv(Correntlv,highest_lv,&t);

	initscr();
	noecho();
	cbreak();

	view=newwin(height,width,0,0);

	keypad(view,TRUE);
	//keypad(stdscr,TRUE);
	//drawMap(stdscr);
	drawMap(view);
	//while(1){
	
	//wtimeout(view,1);
	while (ch != 'q'){

		NowTime=clock();
		deltaTime = NowTime - LastTime;
		LastTime = NowTime;

		if (nodelay(view,TRUE)!= ERR)
			ch = wgetch(view);
		
		controll(p1,view,ch);
		switchlv(Correntlv,p1,highest_lv,view);
		updateScreen(view,Correntlv,p1,deltaTime);
		//switchlv(Correntlv,p1,highest_lv,view);  // check if need to switch the lv
		//updateScreen(view,Correntlv,p1,deltaTime);	//show up the entities and player 
		//if (flagNewlv == TRUE) Correntlv= newlv(Correntlv,num_lv);
		//Correntlv=switchlv();
	
		//if (deltaTime <= TimePerFrame) sleep(TimePerFrame - deltaTime);
	}




	endwin();
	return (0);
}