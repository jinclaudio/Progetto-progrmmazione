//
// Created by jincl on 2021/3/4.
//

#ifndef PROGETTO_BONUS_AND_ENEMY_H
#define PROGETTO_BONUS_AND_ENEMY_H


class bonus_and_enemy {

    protected:
        char *enemy;
        int damage;
        int bonus;
        int x_en;
        int y_en;
        int x_bo;
        int y_bo;
    public:
        bonus_and_enemy();

        int get_bonus(); //lasciamo dopo

        void attack();


};


#endif //PROGETTO_BONUS_AND_ENEMY_H
