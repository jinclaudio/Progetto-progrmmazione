#include <Windows.h>
#include "character.h"
#include "Controls.h"
#include "graphics.h"
#include "map.h"
#include "points.h"
#include "utilities.h"

int main(){
    int index = 0;
    points point = points();
    character hero = character();
    Map map = Map();

    while (point.check_value()){
        move(hero, point);
        hit(hero,point, map, index);
        map.print(index);
        point.add_points(1);
        Score(point.get_value(), map.get_current_difficulty());
        change_level(point, map, index);
        map.shift(index);
        map.last(index);
        index++;
    }

    system("CLS");
    GameOver();
    Sleep(4000);
    exit(0);
}