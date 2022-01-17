//
// Created by jincl on 2022/1/16.
//

#include "Graphics.h"
#include <math.h>
void drawBorder(WINDOW *local_win,livello lv){
    
    wborder(local_win,'|','|','-','-','-','-','-','-');
    if (!lv->DoorOpened) mvwvline(local_win,lv->ExitDoor,width-1,'X',2);
    else mvwvline(local_win,lv->ExitDoor,width-1,' ',2);
    mvwvline(local_win,lv->EntrDoor,0,' ',2);
}
void drawMap(WINDOW *local_win,livello lv) {
    switch (lv->id_map) {

        case 1: {
            mvwhline(local_win, 6, 4, '-', 42);
            for (int i = 10; i < 50; i = i + 10)
                mvwvline(local_win, 3, i, '|', 7);
        }
            break;

        case 2: {
            mvwhline(local_win, 4, 1, '-', 8);
            mvwhline(local_win, 8, 39, '-', 8);
            mvwvline(local_win, 5, 4, '|', 3);
            mvwvline(local_win, 1, 19, '|', 7);
            mvwvline(local_win, 9, 24, '|', 3);
            mvwhline(local_win, 5, 20, '-', 10);
            mvwvline(local_win, 1, 38, '|', 9);

        }
            break;

        case 3: {
            mvwhline(local_win, 6, 10, '-', 30);
            mvwvline(local_win, 3, 25, '|', 7);
        }
            break;
        case 4: {
            for (int y = 4; y < 10; y++) {
                for (int x = 45; x > 0; x -= 5)
                    mvwaddch(local_win, y, x, '/');
            }
        }
            break;


        case 5: {
            for (int x = 3; x < 48; x += 5)
                mvwvline(local_win, 3, x, '|', 7);
        }
            break;

        case 6: {
            mvwvline(local_win, 3, 6, '|', 8);
            mvwvline(local_win, 3, 44, '|', 8);
            mvwhline(local_win, 3, 10, '-', 31);
            mvwhline(local_win, 10, 10, '-', 31);
        }
            break;

        case 7: {
            mvwhline(local_win, 7, 3, '-', 11);
            mvwhline(local_win, 7, 35, '-', 11);
            mvwvline(local_win, 3, 8, '|', 4);
            mvwvline(local_win, 8, 40, '|', 3);
        }
            break;

        case 8: {
            for (int y = 3; y < 13; y += 3)
                mvwhline(local_win, y, 6, '-', 36);
        }
            break;

        case 9: {
            mvwhline(local_win, 7, 3, '-', 4);
            mvwhline(local_win, 3, 19, '-', 8);
            mvwvline(local_win, 5, 20, '|', 4);
            mvwvline(local_win, 3, 38, '|', 6);
        }
            break;

        case 10: {
            mvwhline(local_win, 3, 4, '-', 11);
            mvwhline(local_win, 9, 4, '-', 11);
        }
    }
}
void clearScene(WINDOW *scene){
    int alt=getmaxy(scene);
    int larg=getmaxx(scene);
    for(int y = 1;y< alt-1 ; y++)
        mvwhline(scene,y,1,' ', larg-2);
}

void updateScoretable(WINDOW *local_win, Player &p1){
    clearScene(local_win);
    mvwprintw(local_win,1,3,"Life: %d", p1.getlife());
    mvwprintw(local_win,2,3,"Score: %d",p1.getscore());
    //mvwprintw(local_win,3,3,"conta: %d", p1.getCount());


    wrefresh(local_win);
}


