//
// Created by jincl on 2022/1/16.
//

#include <ctime>
#include "Physics.h"

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

void MonsterMove_type1(Monster &monster, Player &p, int direction) {

    switch (direction) {
        case 1:
            monster.updatenewposition(monster.getpositionx(), monster.getpositiony() - 1);
            break;
        case 2:

            monster.updatenewposition(monster.getpositionx(), monster.getpositiony() + 1);
            break;
        case 3:

            monster.updatenewposition(monster.getpositionx() - 1, monster.getpositiony());
            break;
        case 4:

            monster.updatenewposition(monster.getpositionx() + 1, monster.getpositiony());
            break;
    }
}
void MonsterMove_type2(Monster &monster, Player &p,int direction){
    if(monster.getpositionx() == p.getpositionx()){

        if(monster.getpositiony() > p.getpositiony())
            monster.updatenewposition(monster.getpositionx(),monster.getpositiony()-1);
        else if (monster.getpositiony() < p.getpositiony())
            monster.updatenewposition(monster.getpositionx(),monster.getpositiony()+1);
        else MonsterMove_type1(monster,p,direction); //move randomly calling function for level <10 if player and monster are in the same position
    }

    else if (monster.getpositionx() > p.getpositionx()){

        if(monster.getpositiony() > p.getpositiony()){
            direction = 1 + rand() % 2;
            switch(direction){
                case 1:
                    monster.updatenewposition(monster.getpositionx()-1,monster.getpositiony());
                    break;
                case 2:
                    monster.updatenewposition(monster.getpositionx(),monster.getpositiony()-1);
                    break;
            }
        }

        else if(monster.getpositiony() < p.getpositiony()){
            direction = 1 + rand() % 2;
            switch(direction){
                case 1:
                    monster.updatenewposition(monster.getpositionx()-1,monster.getpositiony());
                    break;
                case 2:
                    monster.updatenewposition(monster.getpositionx(),monster.getpositiony()+1);
                    break;
            }
        }

        else monster.updatenewposition(monster.getpositionx()-1,monster.getpositiony());

    }

    else { //if monster.getpositionx() < monster.getpositionx()
        if(monster.getpositiony() > p.getpositiony()){
            direction = 1 + rand()% 2;
            switch(direction){
                case 1:
                    monster.updatenewposition(monster.getpositionx()+1,monster.getpositiony());
                    break;
                case 2:
                    monster.updatenewposition(monster.getpositionx(),monster.getpositiony()-1);
                    break;
            }
        }

        else if(monster.getpositiony() < p.getpositiony()){
            direction = 1 + rand()% 2;
            switch(direction){
                case 1:
                    monster.updatenewposition(monster.getpositionx()+1,monster.getpositiony());
                    break;
                case 2:
                    monster.updatenewposition(monster.getpositionx(),monster.getpositiony()+1);
                    break;
            }
        }

        else monster.updatenewposition(monster.getpositionx()+1,monster.getpositiony());
    }

}

void MonsterMove_type3(Monster &monster, Player &p,int direction){
    if(monster.getpositionx() == p.getpositionx() || monster.getpositiony() == p.getpositiony() ) {
        MonsterMove_type2(monster,p,direction); //in this case the movement is not diagonal and the same as in levels 10-19
    }

    else if(monster.getpositionx() > p.getpositionx()){ //caso monster a destra di player

        if(monster.getpositiony() > p.getpositiony()) // caso monster sopra player
            monster.updatenewposition(monster.getpositionx()-1,monster.getpositiony()-1);
        else
            monster.updatenewposition(monster.getpositionx()-1,monster.getpositiony()+1); //caso monster sotto player
    }

    else if(monster.getpositionx() < p.getpositionx()){ //caso monster a six di player

        if(monster.getpositiony() > p.getpositiony()) //caso mosnter sopra player
            monster.updatenewposition(monster.getpositionx()+1,monster.getpositiony()-1);
        else
            monster.updatenewposition(monster.getpositionx()+1,monster.getpositiony()+1); //caso monster sotto player
    }
}

void UpdateMonsterPosition(WINDOW *local_win, Monster &monster,float dt, Player &p, int level) {

    CheckPosition(local_win, monster);

    static float timeCounter = 0.0f;
    timeCounter += dt;
    int direction = rand() % 4 + 1;
    if (timeCounter >= 10.0f) {
        timeCounter = 0.0f;

        //RANDOM MOVEMENT for levels 1-9
        if (level <10) {
            MonsterMove_type1(monster,p,direction);
        }

            //NON-DIAGONAL MOVEMENT TOWARDS PLAYER for levels 10-19
        else if (level <20)
            MonsterMove_type2(monster,p,direction);
            //DIAGONAL MOVEMENT TOWARDS PLAYER for levels above 20
        else {
            MonsterMove_type3(monster,p,direction);
        }
        mvwaddch(local_win, monster.getpositiony(), monster.getpositionx(), ' ');
    }
}
void updateMonster(WINDOW *local_win,Monster &monster,float dt){

    if (monster.is_move_okay(local_win,monster.getnewpositionx(),monster.getnewpositiony()))
        monster.updateposition(monster.getnewpositionx(),monster.getnewpositiony());

    mvwaddch(local_win,monster.getpositiony(),monster.getpositionx(),monster.gettext());
}

void updateBonus(WINDOW *local_win,Entity &bonus){
    CheckPosition(local_win,bonus);
    mvwaddch(local_win,bonus.getpositiony(),bonus.getpositionx(),bonus.gettext());
}
void updateEntity(WINDOW *local_win,livello lv,float dt,Player &p1){

    for (int i = 0; i<lv->n_monster;i++) {
        if (lv->monsters[i]->getactive())
            UpdateMonsterPosition(local_win,*(lv->monsters[i]),dt,p1,lv->num_lev);
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
    static float timeCounter = 0.0f;
    timeCounter += dt;
    for (int i = 0; i <lv->n_monster; i++){
        //bullet && monster
        if (bullet_hit(p1, *(lv->monsters[i]) ) ) {
            p1.updateFlag(false);
            mvwaddch(local_win,p1.bulletY(),p1.bulletX()-1,' ');

            lv->monsters[i]->damaged();
            mvwaddch(local_win,lv->monsters[i]->getpositiony(),lv->monsters[i]->getpositionx(),' ');
            if (lv->monsters[i]->getactive()) p1.scored();
        }
        // Player && monsterss

        // Player can be damaged for the second time only after 10 sec.

        if (Player_hit(p1,*(lv->monsters[i])) && timeCounter >= 10.0f) {
            timeCounter = 0.0f;
            int danno;
            switch(mvwinch(local_win,p1.getpositiony(),p1.getpositionx())){
                case 'm':{
                    danno=1;
                }break;
                case 'M':{
                    danno=3;
                }break;
                case 'B':{
                    danno=3;
                }break;
            }
            lv->monsters[i]->damaged();
            p1.damaged(danno);
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
                    mvwvline(local_win,lv->ExitDoor,width-1,' ',2);
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


void updateScreen(WINDOW *local_win,livello lv, Player &p1,float dt){
    dt/=1000.0f;

    clearScene(local_win);
    drawBorder(local_win,lv);
    drawMap(local_win,lv);

    updatePlayer(local_win,p1);
    updateEntity(local_win,lv,dt,p1);

    Hitbox(local_win,lv,p1,dt);

    if (!lv->DoorOpened)
        CheckDoor(local_win,lv);

    napms(20);
}
