
#include "../headers/mappa.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

mappa:: mappa(){
    this->altezza;
    this->lunghezza;}



//il personaggio si rapresenta con P, il nemico si rappresenta con * (si ricorda che ci sono diversi tipi di nemici/bonus)



    void mappa::print_boarders(){
        for(int i = 0; i < this->lunghezza; i++){//disegna il bordo superiore
            cout << "-";
        }
        cout << endl;
        for(int i = 1; i < altezza; i++){ //questo ciclo disegna i bordi laterali e i bordi intermedi
            for (int j = 0; j < lunghezza; j++){
                //if (i == y && j == x){
                //    cout << "P";
                //}
                //else if (i == enemyY && j == enemyX){
                //    cout << "*";
                //}
                /*else*/ if ( i == 2 || i == 4){//disegna i bordi intermedi
                    cout << "-";
                }
                else {//disegna i bordi laterali
                    if (j == 0 ){
                        cout << "#";
                    }
                    cout << " ";
                    //if (j == lunghezza-3){
                    //  cout << "#";
                    //}
                }
            }

            cout << endl;
        }
        for (int i = 0; i< lunghezza; i++){//disegna il bordo inferiore
            cout << "-";
        }
        cout << endl;
        cout << endl;
        cout << endl;
        //cout << "Life: " << life << endl << "Score: " << score << endl;// stampa il punteggio e la vita
    }
//c'e' da aggiugere P come personaggio nel scenario!!!
//si suppone che P iniziale ha coord x = 2(cioe' P e' posizionato all'estremo sinistra del scenario) e
// coord y = 4(cioe' P e' inizializzato nella striscia in mezzo)










