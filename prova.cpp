#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <ncurses.h>
#include <unistd.h>
using namespace std;

#define width 50
#define height 10
const char t = '0';

typedef unsigned int DWORD;

DWORD GetTickCount()
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

struct Vec2 {
	float x;
	float y;
};

class Entity {
	protected:
	Vec2 position;  //位置
	Vec2 velocity;  //速度
	char texture;    //纹理（要显示的图形）
	bool grounded;   //是否在地面上（用于判断跳跃）
	bool active;     //是否存活
	char type;
	public:
	Entity(char tipo, char text){
		this->position.x = 5.0f + rand() % (width - 5);
		this->position.y = 10;
		this->velocity.x = 0;
		this->velocity.y = 0;
		this->texture = text;
		this->grounded = false;
		this->active = true;
		this->type = tipo;
	}
	Vec2 getpostion(){
		return position;
	}
	void updateposition(float x1,float y1){
		position.x=x1;
		position.y=y1;
	}
	float getpositionx(){
		return position.x;
	}
	float getpositiony(){
		return position.y;
	}
	float getvelocityx(){
		return velocity.x;
	}
	float getvelocityy(){
		return velocity.y;
	}
	void updateVelocityX(float x){
		velocity.x = x;
	}
	void updateVelocityY(float y){
		velocity.y = y;
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
	bool getgrounded(){
		return grounded;
	}
	char gettype(){
		return this->type;
	}
	void updateGrounded(bool landed){
		grounded=landed;
	}
	void Death() { 
		this->updateactive(false);
		this->updateVelocityX(0);
		this->updateVelocityY(0); 
	}

	bool is_move_okay(WINDOW *local_win,float y, float x){
	    char testch;

	    /* return true if the space is okay to move into */

	    testch = mvwinch(local_win,y, x);
	    if (testch == '-' || testch == '=') return false;
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
	float flagY;
	float endX;
	
	
	public:
	player(char tipo,char text):Entity(tipo,text){
		this->position.x = 0;
		this->position.y = 10; // 数字越低， 显示的地方越低
		this->life=3;
		this->score=0;
		this->damage = false;
		this->scored = false;
		this->healed = false;
	
	
		this->startX = 0;
		this->endX = width;
		this->flagY = height-2;
		
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

	if ( newlev==0 )
		tmp->name[0] = t;			// if lv == 0, then name = t
	else
		tmp->name[0]= *(lv->name)+1;//  else name = prev.name + 1

	if (newlev < 5)			 // there is only 1 buff when the lv is under 5
		tmp->buff = 1;
	else tmp->buff = newlev-4; 	 // after lv 5, the buff number will add 1 per lv.

	for (int i = 0; i < newlev+1; i ++){
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

void drawMap(WINDOW *local_win){
	wborder(local_win,' ',' ','-','-','-','-','-','-');
	wrefresh(local_win);
}

void controll(player &p1,WINDOW *local_win,int ch){
	bool haveMoved = false;
	//如果玩家死亡，则不能操作
	if (p1.getactive() == true){
		mvwaddch(local_win,height/2,width/2,'A');
		//控制跳跃
		switch(ch){
			case KEY_UP:
				if (p1.getgrounded() == true)
				p1.updateVelocityY(15.0f);
			break;

			case KEY_RIGHT:
				p1.updateVelocityX(5.0f);
				haveMoved = true;
			break;

			case KEY_LEFT:
				p1.updateVelocityX(-5.0f);
				haveMoved = true;
			break;
		}
		//若没有移动，则速度停顿下来
		if (haveMoved != true) {
			p1.updateVelocityX( fmax(0, p1.getvelocityx() * 0.5f) );//使用线性速度的渐进减速
		}
	}
}


void switchlv(livello Correntlv, player &p1, int &highest_lv, WINDOW *local_win){
	if (p1.getpositionx() > width){
		if (Correntlv->next==NULL) {
			Correntlv=newlv(Correntlv,highest_lv,&t); // if there isn't a next lv, create it
		}
		else {
			scr_dump(Correntlv->name[0]);	  // save the screen as a file 
			Correntlv = Correntlv->next;	  //Correntlv is changed in nextLv
			scr_restore(Correntlv->name[0]);  // restore the file as a screen
			doupdate();						// update screen
		}
		mvwaddch(local_win,p1.getflagY(),p1.getstartX(),p1.gettext());  //update the starting position of player
	}

	else if (p1.getpositionx() < 0){
		if (Correntlv->num != 0 ){
			scr_dump(Correntlv->name[0]);	// save the screen as file named
			Correntlv = Correntlv->prev;	// Correntlv is changed in prevLv
			scr_restore(Correntlv->name[0]); // restore the file as a screen
			doupdate();						// update screen
			mvwaddch(local_win,p1.getflagY(),p1.getendX(),p1.gettext()); //update the starting position of player
		};
	};
	wrefresh(local_win);
}
//计算距离的平方
float distanceSq(Vec2 a1, Vec2 a2) {
	float dx = a1.x - a2.x;
	float dy = a1.y - a2.y;
	return dx * dx + dy * dy;
}

//处理碰撞事件
void handleCollision(livello lv, player &p1,int i) { //pending to be modificated

	if (p1.getpositiony() - 0.3f < lv->enemies[i]->getpositiony())
		if (lv->enemies[i]->gettype() == 'm'){
			if (p1.getlife() != 0) p1.updatedamage(true);
			else p1.Death();
		}
	/*if (entity.gettype() == 's'){
		p1.updatescore(true);
		if (p1.getscore() == 100){
		 p1.updateLevel();
		}
	} 

	if (entity.gettype() == 'l') p1.updatelife(true);*/
	// can i use the specific entity as parametre of funci?
	//EntityDie(lv); 
	lv->enemies[i]->Death();
}

//更新物理&碰撞
void collision(livello lv, player &p1, int i){ // pending to be modificated

	float disSqM = distanceSq(lv->enemies[i]->getpostion(), p1.getpostion());
	//float disSqS = distanceSq(score.getpostion(), p1.getpostion());
	//float disSqL = distanceSq(life.getpostion(), p1.getpostion());
	
	//若发生碰撞，则处理该碰撞事件
	if (p1.getactive() == true){
		if (disSqM < 1 * 1  && lv->enemies[i]->getactive()==true )	
			handleCollision(lv,p1,i);
		//else if (disSqS < 1 * 1 && score.getactive()==true)
		//	handleCollision(score,p1);
		//else if (disSqL < 1 * 1 && life.getactive()==true)
		//	handleCollision(life,p1);
	}	
}	
// updatephysics can be void because tha show up immediatly the position; pending to be modificated
void updatePhysicsP(WINDOW *local_win, float dt,player &p1) {
		Vec2 newposition;
		
		//更新实体
		//若实体死亡，则无需更新
		if (p1.getactive() == true){
			//记录原实体位置
			float x0f = p1.getpositionx();
			float y0f = p1.getpositiony();
			int x0 = x0f + 0.5f; 
			int y0 = y0f + 0.5f;
			//记录模拟后的实体位置
					//旧位置 + 时间×速度 = 新位置
			float x1f = fmin(fmax(p1.getpositionx() + dt * p1.getvelocityx(), 0.0f), width - 1); // fmin( fmax(0+1*0,0),49 )=0
			float y1f = fmin(fmax(p1.getpositiony() + dt * p1.getvelocityy(), 1.0f), height - 1); // fmin( fmax(15+1*0,0),49 ) = 15
			int x1 = x1f + 0.5f; 
			int y1 = y1f + 0.5f;
			
			//判断障碍碰撞
			//if (scene->barrier[x0][y1] == true) { // { x0=0, y1=15} = false
			if (p1.is_move_okay(local_win,y1,x0) == false){	
				p1.updateVelocityY(0);
				y1 = y0;
				y1f = y0f;
			};
			//if (scene->barrier[x1][y1] == true) { // { x1=0, y1=15} = false
			if (p1.is_move_okay(local_win,y1,x1) == false){
				p1.updateVelocityX(0);
				x1 = x0;
				x1f = x0f;
			};

			//判断是否踩到地面（位置的下一格），用于处理跳跃
			//if (scene->barrier[x1][] == true) { // {max( x1=1, 14)} = true...
			if (p1.is_move_okay(local_win,(int)fmax( y1-1, 0),x1) == true){	
				//this->grounded=true;
				p1.updateGrounded(true);
			
			}
			else {
				//     增加的速度大小 = 时间*（重力/质量）
				p1.updateVelocityY(p1.getvelocityy()+dt*-29.8f);
				//this->velocity.y = this->velocity.y + dt * (scene->gravity / 1.0f);
				//this->grounded = false;
				p1.updateGrounded(false);
				
			}
			newposition={x1f,y1f}; // { 0 , 15}
			p1.updateposition(x1f,y1f);
			//return newposition;
		} 
}
void updatePhysicsM(WINDOW *local_win,livello lv, float dt, int i) {
		Vec2 newposition;
		
		//更新实体
		//若实体死亡，则无需更新
		if (lv->enemies[i]->getactive() == true){
			//记录原实体位置
			float x0f = lv->enemies[i]->getpositionx();
			float y0f = lv->enemies[i]->getpositiony();
			int x0 = x0f + 0.5f; 
			int y0 = y0f + 0.5f;
			//记录模拟后的实体位置
					//旧位置 + 时间×速度 = 新位置
			float x1f = fmin(fmax(lv->enemies[i]->getpositionx() + dt * lv->enemies[i]->getvelocityx(), 0.0f), width - 1); // fmin( fmax(0+1*0,0),49 )=0
			float y1f = fmin(fmax(lv->enemies[i]->getpositiony() + dt * lv->enemies[i]->getvelocityy(), 1.0f), height - 1); // fmin( fmax(15+1*0,0),49 ) = 15
			int x1 = x1f + 0.5f; 
			int y1 = y1f + 0.5f;
			
			//判断障碍碰撞
			//if (scene->barrier[x0][y1] == true) { // { x0=0, y1=15} = false
			if (lv->enemies[i]->is_move_okay(local_win,y1,x0) == false){	
				lv->enemies[i]->updateVelocityY(0);
				y1 = y0;
				y1f = y0f;
			};
			//if (scene->barrier[x1][y1] == true) { // { x1=0, y1=15} = false
			if (lv->enemies[i]->is_move_okay(local_win,y1,x1) == false){
				lv->enemies[i]->updateVelocityX(0);
				x1 = x0;
				x1f = x0f;
			};

			//判断是否踩到地面（位置的下一格），用于处理跳跃
			//if (scene->barrier[x1][] == true) { // {max( x1=1, 14)} = true...
			if (lv->enemies[i]->is_move_okay(local_win,(int)fmax( y1-1, 0),x1) == true){	
				//this->grounded=true;
				lv->enemies[i]->updateGrounded(true);
			
			}
			else {
				//     增加的速度大小 = 时间*（重力/质量）
				lv->enemies[i]->updateVelocityY((lv->enemies[i]->getvelocityy()+dt*-29.8f));
				//this->velocity.y = this->velocity.y + dt * (scene->gravity / 1.0f);
				//this->grounded = false;
				lv->enemies[i]->updateGrounded(false);
				
			}
			newposition={x1f,y1f}; // { 0 , 15}
			lv->enemies[i]->updateposition(x1f,y1f);
			//return newposition;
		} 
}

void Physics(WINDOW *local_win, float dt, int stepNum,livello lv, player &p1){
	//Vec2 newposP, newposM,newposS,newposL;
	dt /= stepNum;
	for (int i = 0; i < stepNum; i++){
		
		updatePhysicsP(local_win,dt,p1);

		for (int j = 0; j < lv->num-1; j++) {
		updatePhysicsM(local_win,lv,dt,j);

		//newposS=scorelanding(scene,dt,i,score);
		//newposL=lifelanding(scene,dt,i,life);
		//判断实体碰撞
		//collision(monster[i],p1,score[i],life[i]);
		collision(lv,p1,j);
		mvwaddch(local_win,lv->enemies[j]->getpositiony(),lv->enemies[j]->getpositionx(),lv->enemies[j]->gettext());
		//monster[j].updateposition(newposM);
		//score[i].updateposition(newposS);
		//life[i].updateposition(newposL);
		}
		//vb->buffer[1][9] = p1.getpositiony() + 34.0f;
		//p1.updateposition(newposP);
		mvwaddch(local_win,p1.getpositiony(),p1.getpositionx(),p1.gettext());
	};
	wrefresh(local_win);
}

void updateAI(WINDOW *local_win,livello lv,float dt) {
	//简单计时器
	static float timeCounter = 0.0f;
	timeCounter += dt;
	//每2秒更改一次方向（随机方向，可能方向不变）
	if (timeCounter >= 2.0f) {
		timeCounter = 0.0f;
		//改变方向的代码
		for (int i = 0; i < lv->num; ++i) {
			//存活着的怪物才能被AI操控着移动
			if (lv->enemies[i]->getactive() == true) {
				lv->enemies[i]->updateVelocityX(3.0f * (1 - 2 * (rand() % 2)));//(1-2*(rand()%1)要不是 -1要不是1
			}
		}
	}
}

void updateScreen(WINDOW *local_win, livello lv,player &p1, double dt){
	//缩小时间尺度为秒单位，1000ms = 1s
	dt /= 1000.0f;

	//更新怪物AI
	updateAI(local_win,lv,dt);
	//更新物理和碰撞
	//拆分10次模拟
	Physics(local_win,dt,10,lv,p1);
	p1.getdamage();
	p1.scoreUp();
	p1.lifeUp();
}

int main(){
	double TimePerFrame = 1000.0f / 60;//每帧固定的时间差,此处限制fps为60帧每秒
	  //记录上一帧的时间点
	DWORD lastTime = GetTickCount();

	int ch;
	WINDOW *view;

	player p1=player('p','P');

	livello Correntlv = NULL;

	int highest_lv = 0;

	Correntlv=newlv(Correntlv,highest_lv,&t);


	initscr();
	noecho();
	cbreak();
	//view=newwin(height,width,0,0);

	//keypad(view,TRUE);
	keypad(stdscr,TRUE);
	drawMap(stdscr);
	//drawMap(stdscr);
	//while(1){
	while (ch != 'q'){
		//mvwaddch(view,height/2,width/2,'A');

		/*DWORD nowTime = GetTickCount();      //获得当前帧的时间点
		DWORD deltaTime = nowTime - lastTime;  //计算这一帧与上一帧的时间差
		lastTime = nowTime;                   //更新上一帧的时间点*/

		if (nodelay(stdscr,TRUE)!= ERR)
			ch = getch();
		
		controll(p1,stdscr,ch);
		switchlv(Correntlv,p1,highest_lv,stdscr);  // check if need to switch the lv
		//updateScreen(stdscr,Correntlv,p1,deltaTime);	//show up the entities and player 
		//if (flagNewlv == TRUE) Correntlv= newlv(Correntlv,num_lv);
		//Correntlv=switchlv();
	
		//if (deltaTime <= TimePerFrame) sleep(TimePerFrame - deltaTime);
	}




	endwin();
	return (0);
}