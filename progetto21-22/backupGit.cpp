#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <ncurses.h>
using namespace std;

#define  width 50
#define  height 13

struct Vec2 {
	int x;
	int y;
};
struct bullet{
	bool flag;
	int x;
	int y;
	char shape;
	int num;
};

class Entity {
	protected:
	Vec2 position;  //位置
	
	char texture;    //纹理（要显示的图形）
	bool active;     //是否存活
	char type;
	int cont;
	public:
	Entity(char tipo, char text){
		this->position.x = rand() % (width-2) + 1;
		this->position.y = rand() % (height-3) + 2;
		this->texture = text;
		this->active = true;
		this->type = tipo;
		this->cont=0;
	}
	void updateposition(int x0,int y0){
		position.x=x0;
		position.y=y0;
	}
	int getpositionx(){
		return position.x;
	}
	int getpositiony(){
		return position.y;
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
		active=false;
		texture=' ';
	}
	bool is_move_okay(WINDOW *local_win,int x, int y){
	    char testch;
	    testch = mvwinch(local_win,y, x);
	    if (testch== '-' || testch== '|' || testch=='X') return false;
	    else return true;
	}
	int getcont(){
		return cont;
	}
	void conta(){
		cont++;
	}
};
class Monster : public Entity{
	protected:
	Vec2 newposition;  //新位置
	int life;
	
	public:
	Monster(char tipo,char text,int life):Entity(tipo,text){
		this->newposition = {0,0};
		this->life=life;
	}
	int getnewpositionx(){
		return newposition.x;
	}
	int getnewpositiony(){
		return newposition.y;
	}
	void updatenewposition(int x1,int y1){
		newposition.x=x1;
		newposition.y=y1;
	}
	int getlife(){
		return life;
	}

	void damaged(){
		life--;
		if (life <= 0) this->Death();
	}
};
class Player : public Monster{
	protected:
	int score;
	int startX;
	int endX;
	int flagY;
	bullet bull;

	public:
	Player(char tipo,char text,int life):Monster(tipo,text,life){
		this->position.x = 1;
		this->position.y = height-2; // 数字越低， 显示的地方越低
		this->score=0;
		this->startX = 1;
		this->endX = width-2;
		this->flagY = height-2;
		this->bull={false,0,0,'>'};
		cont = 0;
	}
	int getflagY(){
		return flagY;
	}
	int getstartX(){
		return startX;
	}
	int getendX(){
		return endX;
	}
	
	int getscore(){
		return score;
	}

	void scored(){
		score +=10;
	}
	void lifeUP(){
		life++;
	}
	
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
	
	void updatebullet(int x,int y){
		bull.x=x;
		bull.y=y;
	}
	int bulletX(){
		return bull.x;
	}
	int bulletY(){
		return bull.y;
	}
};
struct Level{
	int num;
	int n_monster;
	int n_bonus;
	int id_map;
	bool tp_flag= false;
	bool Show_tp=false;
	bool DoorOpened = false;
	bool Drawed=false;
	Entity *bonus[5]; 
	Entity *telep[2];
	Monster *monsters[10];
	Level *next;
	Level *prev;	
};

typedef Level* livello;

void rectangle(WINDOW *local_win, int x, int y, int long1, int long2){
	mvwhline(local_win, y, x, '-', long1+1);
	mvwhline(local_win, y+long2-1, x, '-', long1+1);
	mvwvline(local_win, y, x, '|', long2);
	mvwvline(local_win, y, x+long1+1, '|', long2);	
}
void drawBorder(WINDOW *scene,WINDOW *scoretable){
	box(scoretable, '|', '*');
	wborder(scene,'|','|','-','-','-','-','-','-');
	
	mvwvline(scene,10,0,' ',2);
}

void drawScene(WINDOW *local_win,livello lv){
		switch(lv->id_map){

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
	if (!lv->DoorOpened) mvwvline(local_win,10,width-1,'X',2);
	else mvwvline(local_win,10,width-1,' ',2);

}
void clearScene(WINDOW *scene){
	int alt=getmaxy(scene);
	int larg=getmaxx(scene);
	for(int y = 1;y< alt-1 ; y++)
		mvwhline(scene,y,1,' ', larg-2);
}
void updateScoretable(WINDOW *local_win, Player &p1,livello lv){
	clearScene(local_win);
	mvwprintw(local_win,1,3,"Life: %d", p1.getlife());
	mvwprintw(local_win,2,3,"Score: %d",p1.getscore());
	mvwprintw(local_win,3,3,"id_map: %d",lv->id_map);
	mvwprintw(local_win,4,3,"px: %d",p1.getpositionx());
	mvwprintw(local_win,5,3,"py: %d",p1.getpositiony());
	mvwprintw(local_win,6,3,"tx: %d",lv->telep[1]->getpositionx());
	mvwprintw(local_win,7,3,"ty: %d",lv->telep[1]->getpositiony());
	mvwprintw(local_win,8,3,"T cont: %d", lv->telep[1]->getcont());
	mvwprintw(local_win,9,3,"p cont: %d", p1.getcont());


	/*if (!lv->telep[1]->getactive()) mvwprintw(local_win,9,3,"state: %d",lv->id_map/2);
	else mvwprintw(local_win,9,3,"state: %d",lv->id_map);*/
	wrefresh(local_win);
}
void clearMonster(WINDOW *local_win, Entity &monster){

	mvwaddch(local_win,monster.getpositiony(),monster.getpositionx(),' ');
}
livello newlv(livello lv, int &newlv){
		livello tmp;
		tmp = new Level;
	//set lv;
		tmp->num=newlv;
		
	// init. the number of monster and bonus
		if (newlv<=10){
			if (newlv<=5) tmp->n_bonus = 1; //there is no buff until lv 5
			else tmp->n_bonus = newlv-5; // after lv 5, will increase a buff for each level 

			tmp->n_monster=newlv;
		}
		else {
			tmp->n_monster=10; // after lv 10, the monster s number is always 10
			tmp->n_bonus=5; // 5 for bonus
		}

	// init. monster and bonus
		
		bool key_flag = false;

		if (newlv<=10){

			//monster part
			for (int i = 0; i < tmp->n_monster; i ++){

				int i_monster = rand() % 100 + 1;

				if (i_monster <=75) tmp->monsters[i]= new Monster('m','m',1);
				else tmp->monsters[i]= new Monster('m','M',3);
			}

			//bonus part
			for (int j = 0; j<tmp->n_bonus;j++){

				int if_key = rand() % 100 + 1;

				if (if_key <= 10 && !key_flag) {
					tmp->bonus[j]= new Entity('k','K');
					key_flag = true;
				}
				else tmp->bonus[j]= new Entity('h','H');
			}
		}
		else if (newlv<=30){
			//monster part
			for (int i = 0; i < tmp->n_monster; i ++){

				int i_monster = rand() % 100 + 1;

				if (i_monster <=50) tmp->monsters[i]= new Monster('m','m',1);
				else tmp->monsters[i]= new Monster('m','M',3);
			}
			//bonus part
			for (int j = 0; j<tmp->n_bonus;j++){

				int if_key = rand() % 100 + 1;

				if (if_key <=25 && !key_flag) {
					tmp->bonus[j]= new Entity('k','K');
					key_flag = true;					
				}
				else tmp->bonus[j]= new Entity('h','H');
			}
		}
		else if (newlv>30){
			// monster part
			for (int i = 0; i <tmp-> n_monster; i ++){
				int i_monster = rand() % 100 + 1;
				if (i_monster <=10) tmp->monsters[i]= new Monster('m','M',3);
				else tmp->monsters[i]= new Monster('m','B',newlv/10);
			}
			// bonus part
			for (int j = 0; j<tmp->n_bonus;j++){

				int if_key = rand() % 100 + 1;

				if (if_key <= 40 && !key_flag) {
					tmp->bonus[j]= new Entity('k','K');
					key_flag = true;
				}
				else tmp->bonus[j]= new Entity('h','H');
			}
		}
	
	int if_tp = rand() % 100 + 1;

	//if (if_tp<= 100 && newlv >5) {

	if (if_tp<= 100 ) {
		tmp->Show_tp = true;
		tmp->tp_flag = true;
		tmp->telep[0]= new Entity('t','t');
		tmp->telep[1]= new Entity('t','T');
	}


	tmp->prev = lv;
	tmp->next = NULL;

	if (lv != NULL) lv->next = tmp;
	//tmp->id_map=1;
	//tmp->id_map = rand() % 4 +1;
	if (newlv%2 == 0)
		tmp->id_map=0;
	else tmp->id_map=100;

	newlv++;

	return tmp;
}
livello switchlv(livello Correntlv, Player &p1, int &highest_lv, WINDOW *local_win){
	

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
		drawScene(local_win,Correntlv);
		
	
		return Correntlv;
}
void controll(Player &p1,WINDOW *local_win,int &ch){

	//you can controll only if the Player is alive
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
void updatePlayer(WINDOW *local_win,Player &p1){
	//Player part
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
bool bullet_hit(Player &p1,Entity &e){
	return((p1.bulletX() == e.getpositionx()) && 
		   (p1.bulletY() == e.getpositiony()) &&
		   (p1.bulletFlag()) &&
		   (e.getactive()));
}
bool Player_hit(Player &p1, Entity &e){

	return( (p1.getpositionx() == e.getpositionx()) && 
			(p1.getpositiony() == e.getpositiony()) &&
			e.getactive() );
}
void UpdateMonsterPosition(WINDOW *local_win, Monster &monster,float dt){
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
void CheckPosition(WINDOW *local_win, Entity &e){
	int x1=e.getpositionx();
	int y1=e.getpositiony();

	if(e.getactive() && !e.is_move_okay(local_win,x1,y1) ){ 
		
		//if (mvwinch(local_win,y1,x1) != ' '){
			while(!e.is_move_okay(local_win,x1,y1)){

				if (e.gettype()=='t') x1= rand() % (width/2) +1; // only half map
				else  x1=rand() % (width-2) + 1 ;

				y1=rand() % (height-2) + 1;
			};
			e.updateposition(x1,y1);
		
	}
}
void updateMonster(WINDOW *local_win,Monster &monster,float dt){

		CheckPosition(local_win,monster);

		UpdateMonsterPosition(local_win,monster,dt);

		if (monster.is_move_okay(local_win,monster.getnewpositionx(),monster.getnewpositiony()))
			monster.updateposition(monster.getnewpositionx(),monster.getnewpositiony());

		mvwaddch(local_win,monster.getpositiony(),monster.getpositionx(),monster.gettext());
}
void updateBonus(WINDOW *local_win,Entity &bonus){
	CheckPosition(local_win,bonus);
	if (bonus.getactive())
	mvwaddch(local_win,bonus.getpositiony(),bonus.getpositionx(),bonus.gettext());
}
void updateEntity(WINDOW *local_win,livello lv,float dt){
	for (int i = 0; i<lv->n_monster;i++) {
		if (lv->monsters[i]->getactive())
		updateMonster(local_win,*(lv->monsters[i]),dt);
	}
	
	for(int i = 0; i<lv->n_bonus;i++) {

		if (lv->bonus[i]->getactive())
		updateBonus(local_win,*(lv->bonus[i]));
	}

	if (lv->tp_flag && lv->n_bonus!=0) {
		
		int x1,y1;
		int i_bonus = rand() % lv->n_bonus;

		x1=lv->bonus[i_bonus]->getpositionx();
		y1=lv->bonus[i_bonus]->getpositiony();

		if (lv->bonus[i_bonus]->is_move_okay(local_win,x1+1,y1))
			x1+=1;
		else if (lv->bonus[i_bonus]->is_move_okay(local_win,x1-1,y1))
			x1-=1;
		else if (lv->bonus[i_bonus]->is_move_okay(local_win,x1,y1+1))
			y1+=1;
		else if (lv->bonus[i_bonus]->is_move_okay(local_win,x1,y1-1))
			y1-=1;

		lv->telep[0]->updateposition(x1,y1);

		x1=rand() % (width/2) + 1;
		y1=rand() % (height-2) + 1;

		lv->telep[1]->updateposition(x1,y1);

		CheckPosition(local_win,*(lv->telep[1]));

		lv->tp_flag=false;
	};

	if (lv->Show_tp){
		for (int i = 0; i < 2 ; i++) {
			if (lv->telep[i]->getactive())
			updateBonus( local_win,*(lv->telep[i]));
		}

	}
}
void Hitbox(WINDOW *local_win,livello lv, Player &p1,float dt){
	
	for (int i = 0; i <lv->n_monster; i++){
		//bullet && monster
		   	if (bullet_hit(p1, *(lv->monsters[i]) ) ) {
			    p1.updateFlag(false);
				mvwaddch(local_win,p1.bulletY(),p1.bulletX()-1,' ');
			    lv->monsters[i]->damaged();
			    clearMonster(local_win,*(lv->monsters[i]));
			    p1.scored();
		   }
	   // Player && monsterss
			static float timeCounter = 0.0f;
			timeCounter += dt;
			// Player can be damaged for the second time only after 10 sec.

		   	if (Player_hit(p1,*(lv->monsters[i])) && timeCounter >= 10.0f) {
				   timeCounter = 0.0f;
				   lv->monsters[i]->damaged();
				   p1.damaged();
		   }
	}
	for (int i = 0; i < lv->n_bonus;i++) {

		if (Player_hit(p1,*(lv->bonus[i]) ) )

			switch(mvwinch(local_win,p1.getpositiony(),p1.getpositionx()) ){

				case 'H':{
					lv->bonus[i]->Death();
					mvwaddch(local_win,p1.getpositiony(),p1.getpositionx(),p1.gettext());
					p1.lifeUP();
				} 
				break;

				case 'K':{
					lv->bonus[i]->Death();
					lv->DoorOpened=true;
					mvwvline(local_win,10,width-1,' ',2);
				}
				break;

			}
	}
	for (int i = 0; i < 2;i++){

		if (Player_hit(p1,*(lv->telep[i]) ) ){

			

			switch(mvwinch(local_win,p1.getpositiony(),p1.getpositionx()) ){
				case 't':{
					lv->telep[0]->Death();
					mvwaddch(local_win,lv->telep[1]->getpositiony(),lv->telep[1]->getpositionx(),p1.gettext());
					p1.updateposition(lv->telep[1]->getpositionx(),lv->telep[1]->getpositiony());
					lv->telep[1]->Death();
				}
				break;
				case 'T':{
					
					lv->telep[1]->Death();

					mvwaddch(local_win,lv->telep[0]->getpositiony(),lv->telep[0]->getpositionx(),p1.gettext());
					p1.updateposition(lv->telep[0]->getpositionx(),lv->telep[0]->getpositiony());

					lv->telep[0]->Death();
				}
				break;
			};
			p1.updatenewposition(p1.getpositionx(),p1.getpositiony());
		}
	}
}
void CheckDoor(WINDOW *local_win, livello lv){
	int i = 0;
	bool ak = true;

	while (ak && i !=lv->n_monster){

		if (lv->monsters[i]->getactive()) ak = false;

		else i++;
	}

	if (ak){
		mvwvline(local_win,10,width-1,' ',2);
		lv->DoorOpened=true;
	}
}
void updateScreen(WINDOW *local_win,livello lv, Player &p1,float dt){
	dt/=1000.0f;
	
	updatePlayer(local_win,p1);
	updateEntity(local_win,lv,dt);

	Hitbox(local_win,lv,p1,dt);

	if (!lv->DoorOpened)
		CheckDoor(local_win,lv);

	napms(20);
}

int main(){
	clock_t NowTime,LastTime,deltaTime;
	LastTime = clock();
	srand(time(0));
	int ch;
	WINDOW *view,*scoretable;
	
	Player p1=Player('p','P',3);

	livello Correntlv = NULL;
	

	int highest_lv = 1;
	

	Correntlv=newlv(Correntlv,highest_lv);

	initscr();
	noecho();
	cbreak();
	

	view=newwin(height,width,0,0);
	scoretable=newwin(13,20,0,width+1);

	drawBorder(view,scoretable);

	keypad(view,TRUE);

	while (ch != 'q' && p1.getactive()){

		NowTime=clock();
		deltaTime = NowTime - LastTime;
		LastTime = NowTime;

		if (nodelay(view,TRUE)!= ERR)
			ch = wgetch(view);

		controll(p1,view,ch);

		Correntlv=switchlv(Correntlv,p1,highest_lv,view);
		
		updateScreen(view,Correntlv,p1,deltaTime);
		updateScoretable(scoretable,p1,Correntlv);

		//if (!p1.getactive()) ch = 'q';
		wrefresh(view);
		
	}
	napms(250);
	endwin();

	return (0);
}