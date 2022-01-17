#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <ncurses.h>

#include "Physics.h"
using namespace std;





int main(){
    clock_t NowTime,LastTime,deltaTime;
    LastTime = clock();
    srand(time(0));
    int ch;
    WINDOW *view,*scoretable;
    
    Player p1= Player('p', 'P', 3);
    p1.updateFlag(false);

    livello Correntlv = NULL;
    

    int highest_lv = 1;
    

    Correntlv=newlv(Correntlv,highest_lv);

    initscr();
    noecho();
    cbreak();

    curs_set(0);
    view=newwin(height,width,0,0);
    scoretable=newwin(13,20,0,width+1);
    box(scoretable, '|', '*');
    

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
        updateScoretable(scoretable,p1);

        wrefresh(view);
        
    }
    napms(250);
    endwin();

    return (0);
}