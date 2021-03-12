//
// Created by jincl on 2021/3/4.
//

#ifndef PROGETTO_BONUS_AND_ENEMY_H
#define PROGETTO_BONUS_AND_ENEMY_H


//Non-Playable-Character: puo` essere un bonus, un nemico, un boss.
//Queste saranno sottoclassi o sotto-sottoclassi, in modo da sfruttare l'ereditarieta`.

//Alcune idee:  boss sottoclasse di nemico sottoclasse di NPC (ad es. boss e` un nemico molto forte che compare una volta raggiunta una soglia di punteggio)
//oppure:       buff sottoclasse di bonus sottoclasse di NPC (ad es. buff puo` aumentare la statistica life ogni 10 passi)

class NPC{
    const int WIDTH = 18;
    const int LENGTH = 40;
protected:
    char *symbol;   //carattere per grafica ASCII dell'NPC
    bool is_there;  //variabile booleana per determinare se l'NPC e` ancora presente
    int x_NPC;      //posizione x NPC
    int y_NPC;      //posizione y NPC

public:
    NPC(char symbol=" ", bool is_there=true, int x=0, int y=0); //costruttore

    void setup(char symbol, bool is_there=true, int x, int y);

    void print();

    void taken(); //metodo che rende preso/ucciso un NPC bonus/nemico, settando is_there a false

    bool match(personaggio p); //metodo che restituisce true, se la posizione dell'NPC e del personaggio coincidono

    //metodi della forma get_field
    char get_symbol();
    bool get_is_there();
    int get_x_NPC();
    int get_y_NPC();

    //metodi della forma set_field
    void set_symbol(char *symbol);
    void set_is_there(bool is_there);
    void set_x_NPC(int x);
    void set_y_NPC(int y);
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class bonus : public NPC{
protected:
    int bonus_life;
    int bonus_points;
    //int bonus_mana;

public:
    bonus(char NPC=" ", bool is_there=true, int x=0, int y=0, int bonus_life, int bonus_points) : NPC(NPC, is_there, x, y); //costruttore

    //taken ereditato da NPC

    void apply_bonus(personaggio &p); //Applica il bonus al personaggio p che si trova nella stessa posizione del bonus

    //nuovi metodi get_field
    int get_bonus_life();
    int get_bonus_points();
    //int get_bonus_mana();

    //nuovi metodi set_field
    void set_bonus_life(int bonus_life);
    void set_bonus_points(int bonus_points);
    //void set_bonus_mana();
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class enemy : public NPC{
protected:
    int enemy_life;
    int damage_life;
    int damage_points;
    //int damage_mana;

public:
    enemy(char NPC=" ", bool is_there=true, int x=0, int y=0, int enemy_life=0 int damage_life=0, int damage_points=0) : NPC(NPC, is_there, x, y); //costruttore

    //taken ereditato da NPC

    void apply_damage(personaggio &p);

    //nuovi metodi get_field;
    int get_enemy_life();
    int get_damage_life();
    int get_damage_points();

    //nuovi metodi set_field;
    void set_enemy_life(int enemy_life);
    void set_damage_life(int damage_life);
    void set_damage_points(int damage_points);

};

/*
class bonus{

    protected:
        char *bonus;
        int bonus_points;
        int bonus_life;
        int x_bonus;
        int y_bonus;
        bool bonus_taken; //true, se il personaggio ha preso il bonus, false altrimenti (per mappa dinamica);
    public:
        bonus(); //constructor

        int get_bonus_life(){
            return this->bonus_life;
        }


        //Funzioni get_field
        int get_bonus_points(){
            return this->bonus_points;
        }

        int get_bonus_life(){
            return this->bonus_life;
        }

        int get_x_bonus(){
            return this->x_bonus;
        }

        int get_y_bonus(){
            return this->y_bonus;
        }

        bool get_bonus_taken(){
            return this->bonus
        }



};

class enemy{};
 */


#endif //PROGETTO_BONUS_AND_ENEMY_H
