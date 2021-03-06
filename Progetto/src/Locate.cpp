//
// Created by jincl on 2021/2/27.
//

#include "../headers/Locate.h"
#include <windows.h>

void Locate(int x, int y)
{
    COORD point = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}