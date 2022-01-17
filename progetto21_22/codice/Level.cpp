//
// Created by jincl on 2022/1/16.
//

#include "Level.h"
#include "Structs.h"
#include <math.h>
livello newlv(livello lv, int &newlv){
        livello tmp;
        tmp = new Level;
    //set lv;
        tmp->num_lev=newlv;
        
    // init. the number of monster and bonus
        if (newlv<=10){
            if (newlv<=5) tmp->n_bonus = 0; //there is no buff until lv 5
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

                if (if_key <= 10 && !key_flag) { //modifica
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

    if (if_tp<= 50 && tmp->n_bonus != 0) {
        tmp->Show_tp = true;
        tmp->tp_flag = true;
        tmp->telep[0]= new Entity('t','t');
        tmp->telep[1]= new Entity('t','T');
    }


    tmp->prev = lv;
    tmp->next = NULL;

    if (lv != NULL) lv->next = tmp;

    tmp->id_map = rand() % 10 +1;


    newlv++;

    return tmp;
}
livello switchlv(livello Correntlv, Player &p1, int &highest_lv, WINDOW *local_win){
    if (p1.getnewpositionx() >= width){
        if (Correntlv->next == NULL)
            Correntlv=newlv(Correntlv,highest_lv); // if there isn't a next lv, create it
        else Correntlv = Correntlv->next;     //Correntlv is changed in nextLv

        p1.updatenewposition(1,Correntlv->EntrDoor);
    }
    else if (p1.getnewpositionx() < 0 && Correntlv->num_lev != 1){
        Correntlv = Correntlv->prev;    // Correntlv is changed in prevLv
        p1.updatenewposition(48,Correntlv->ExitDoor);
    };
    return Correntlv;
}