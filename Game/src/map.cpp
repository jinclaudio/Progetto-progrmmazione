#include "map.h"

#define LENGTH 100
#define WIDTH 50
#define DISPLAY 60
#define OFFSET_X 15
#define OFFSET_Y 5
using namespace std;

Map :: Map() {
    //creare il primo livello
    this->level = new Level;
    this->level->difficulty = 1;
    this->level->segment = NULL;
    new_segment(this->level->difficulty);
    this->level->next = NULL;
    this->level->prev = NULL;

    //impostare
    this->current_difficulty = 1;
    this->segment_current = this->level->segment;
    this->segment_next = NULL;
    this->segment_prev = NULL;

}

int Map :: get_current_difficulty(){
    return current_difficulty;
}

pSegment Map :: get_current_segment(){
    return this->segment_current;
}

pSegment Map::get_next_segment(){
    return this->segment_next;

}

pSegment Map::get_prev_segment(){
    return this->segment_prev;
}

pLevel Map::get_current_level(){
    return this->level;
}

void Map::new_level(){
    //crea il prossimo livello, i indica la difficolta del livello
    int i = 2;
    pLevel tmp = this->level;

    while (tmp->next != NULL){
        tmp = tmp->next;
        i++;
    }
    tmp->next = new Level;
    tmp->next->difficulty = i;
    tmp->next->segment = NULL;
    tmp->next->next = NULL;

}

void Map::new_segment(int difficulty){
    pSegment tmp = new Segment;
    tmp->next = NULL;

    for (int i=0; i < LENGTH; i++){
        for (int j=0; j < WIDTH-1; j++){
            if (j == 0 || j == WIDTH - 1){
                tmp->canvas[i][j] = '+';
            }
            else{
                tmp->canvas[i][j] = ' ';
            }
        }
    }
    //calcolare numero di nemici nel livello
    //lasciamo per dopo

    
}

void Map::shift(int x) {
    int r = x % WIDTH;
    //controlla r, se la condizione è veram significa che la prossima iterazione
    //è completamente stampata, quindi si passa al prossimo segmento
    if (r == 49){
        this->segment_current = this->segment_next;
        this->segment_next = this->segment_next->next;
    }
}

void Map::last(int x) {
    int r = x % WIDTH;
    //se non esiste il prossimo segmento, lo crea
    if (r == 30){
        if (this->segment_next == NULL){
            new_segment(this->current_difficulty);
            this->segment_next = this->segment_current->next;
        }
    }
}

void Map::level_up() {
    int i = 1;
    int n = this->current_difficulty;
    pLevel tmp = this->level;
    //cerca il prossimo livello, che è current_difficulty + 1
    while (i<n){
        tmp = tmp->next;
        i++;
    }
    // i è la difficoltà che va ad aumentare
    i = i+1;
    //se non esiste il prissimo livello, lo si crea con la diffcoltà che ha
    if (tmp->next == NULL){
        new_level();
        new_segment(i);
    }
    this->segment_next = tmp->next->segment;
}

void Map::level_down() {
    //funzione che ci serve quando si torna all' indietro
    int i = 1;
    int n = this->current_difficulty-1;
    pLevel tmp = this->level;
    //cerca il livello precedente
    while (i<n){
        tmp = tmp->next;
        i++;
    }
    //tornare al segmento precedente
    this->segment_next = tmp->segment;
}

void Map::print(int x) {
    pSegment tmp = new Segment;
    pSegment pre = new Segment;
    int q = (x + DISPLAY)/WIDTH;
    int r = x % WIDTH;
    //se q è 0 significa che x indica il primo segmento
    //se r è maggiore di 60, significa che il livello da stampare è nel segmento
    if (r < 80){
        //stampa il livello
        for (int i=0; i<DISPLAY; i++){
            for (int j = 0; j < LENGTH; j++){
                gotoxy(j+OFFSET_X, i + OFFSET_Y);
                cout << this->segment_current->canvas[i+(x%WIDTH)][j];
            }
        }
    }
    else{
        q = WIDTH-r;
        //stampa il primo segmento
        for (int i=0; i < q; i++){
            for (int j = 0; i < LENGTH; j++) {
                gotoxy(j + OFFSET_X, i + OFFSET_Y);
                cout << this->segment_current->canvas[x % WIDTH+i][j];

            }
        }
        //stampa il secondo segmento
        for (int i=0; i<DISPLAY; i++){
            for (int j= 0; j <LENGTH; j++){
                gotoxy(j+ OFFSET_X, i + OFFSET_Y);
                cout << this->segment_next->canvas[i-q][i];
            }
        }
    }

}