
#include "utilities.h"

void gotoxy(int x,int y){
    COORD position;
    position.X=x;
    position.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void hideCursor(){
 CONSOLE_CURSOR_INFO cursor_info = {1, 0};
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
