#include <iostream>
#include <cstring>



class personaggio{
protected:
    char *symbol;
    int life;
    int points;
    int x_pos;
    int y_pos;

public:
    personaggio(char symbol = ' ', int life=100, int points=0, int x_pos=0, int y_pos=0);  //costruttore

    void setup();   //inizializzazione

    void print_s(); // stampa il personaggio sulla mappa

    void print_points(); //stampa il punteggio
    void print_life();  // stampa la vita

    int get_x_pos(); // ottieni la coordianta di p in x
    int get_y_pos(); // ottieni la coordinata di p in y
    int get_points(); // lettura di punteggio
    int get_life();

    void set_x_pos(int x);
    void set_y_pos(int y);
    void set_points(int points);
    void set_life(int life);

};

