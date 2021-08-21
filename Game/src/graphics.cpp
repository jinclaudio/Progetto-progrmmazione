//
// Created by jincl on 2021/8/19.
//

#include "graphics.h"
#include "utilities.h"
#include <iostream>

#define BEGIN 0
#define LENGTH 100
#define WIDTH 50
#define POS_X_TEXT 110
#define POS_Y_TEXT 2

using namespace std;

char TopCornerLeft = '*';
char TopCornerRight = '*';
char MiddleTop = '*';
char MiddleBottom = '*';
char BottomCornerLeft = '*';
char BottomCornerRight = '*';
char Raw = '*';
char Column = '*';

void Border() {
    //stampa colonne
    for (int i = 1; i < LENGTH; i++){
        // da (0,1) a (0,100)
        gotoxy(BEGIN, i);
        cout << Column;
        // da (50,1) a (50,100)
        gotoxy(WIDTH, i);
        cout << Column;
    }
    //stampa righe
    for (int i = 1; i < WIDTH; i++){
        // da (1,0) a (50,0)
        gotoxy(i, BEGIN);
        cout << Raw;
        // da (1, 100) a (49,100)
        gotoxy(i, LENGTH);
        cout << Raw;
    }
    // stampa gli spigoli
    gotoxy(BEGIN, BEGIN);
    cout << TopCornerLeft;
    gotoxy(WIDTH, BEGIN);
    cout << TopCornerRight;
    gotoxy(BEGIN, LENGTH);
    cout << BottomCornerLeft;
    gotoxy(WIDTH, LENGTH);
    cout << BottomCornerRight;
}




void Score(int score, int difficulty){
    Border();
    // un altro bordino all'interno
    for (int i = BEGIN; i <= LENGTH; i++){
        gotoxy(POS_X_TEXT-2, i);
        cout << Column;
    }
    gotoxy(POS_X_TEXT-2, BEGIN);
    cout << MiddleTop;
    gotoxy(POS_X_TEXT-2, LENGTH);
    cout << MiddleBottom;

    int PosText = POS_Y_TEXT;

    //stampa punteggio e livello
    gotoxy(POS_X_TEXT, PosText);
    cout << "SCore: " << score;
    PosText = PosText + 1;
    gotoxy(POS_X_TEXT, PosText);
    cout << "Level: " << difficulty;
    PosText = PosText + 2;
    //stampa le istruzioni
    gotoxy(POS_X_TEXT, PosText);
    cout << "Move left: A";
    PosText = PosText + 1;
    gotoxy(POS_X_TEXT, PosText);
    cout << "Move right: D";
    PosText = PosText + 2;
    gotoxy(POS_X_TEXT, PosText);
    cout << "Move up: W";
    PosText = PosText + 1;
    gotoxy(POS_X_TEXT, PosText);
    cout << "Move down: S";
    PosText = PosText + 2;
}

void GameOver(){
    Border();
    gotoxy(WIDTH/2, LENGTH/2);
    cout << "GAME OVER" ;
}

void Intro() {
    Border();
    gotoxy(WIDTH/2, LENGTH/2);
}
