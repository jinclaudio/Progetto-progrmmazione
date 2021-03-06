

class personaggio{
protected:
    char *symbol;
    int life;
    int score;
    int x_pos;
    int y_pos;

public:
    personaggio(); //costruttore

    void Setup(); //inizializzazione

    void print_s(); // stampa il personaggio sulla mappa

    int get_x_pos(); // ottieni la coordianta di p in x
    int get_y_pos(); // ottieni la coordinata di p in y
    void print_score(); //stampa il punteggio
    void print_life(); // stampa la vita
    int get_score(); // lettura di punteggio

};