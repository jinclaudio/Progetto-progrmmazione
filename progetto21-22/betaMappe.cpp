//mappe
#include <ncurses.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

/* function

横向画线
int mvwhline(WINDOW *win, int y（ 起始高度 从上到下 0最高）, int x （起始宽度 从左到右 0最左）, chtype ch （文字）, int n （数量）);

纵向画线
int mvwvline(WINDOW *win, int y, int x, chtype ch, int n);

*/
void draw1(WINDOW *local_win){
	mvwhline(local_win,  6,  1,  '-', 46);
	for (int i = 7;i < 45; i = i+8)
		mvwvline(local_win, 3, i, '|', 3);

	for (int i = 3; i < 45; i = i+8)
		mvwvline(local_win, 7, i, '|', 3);

	for (int i = 3; i < 50; i = i+8)
		mvwvline(local_win, 1, i, '|', 3);

	for (int i = 7; i < 45; i = i+8)
		mvwvline(local_win, 9, i, '|', 3);

	mvwvline(local_win, 4, 0, ' ', 2);
	mvwvline(local_win, 8, 0, 'X', 2);

}

void draw2(WINDOW *local_win){
	mvwhline(local_win,  6,  1,  '-', 48);
	for (int i = 10; i < 50; i = i+10)
		mvwvline(local_win, 1, i, '|', 11);

	mvwvline(local_win,  8,  0,  ' ', 2);
	mvwhline(local_win,  12,  45,  'X', 2);

}

void draw3(WINDOW *local_win){
	mvwhline(local_win,  4,  1,  '-', 8);
	mvwhline(local_win,  8,  39,  '-', 8);
	mvwvline(local_win, 5, 4, '|', 3);
	mvwvline(local_win, 1, 19, '|', 7);
	mvwvline(local_win, 9, 24, '|', 3);
	mvwhline(local_win,  5,  20,  '-', 10);
	mvwvline(local_win, 1, 38, '|', 9);
	mvwvline(local_win, 9, 0, ' ', 2);
	mvwvline(local_win, 1, 49, 'X', 2);

}

void rectangle(WINDOW *local_win, int x, int y, int long1, int long2){
	mvwhline(local_win, y, x, '-', long1+1);
	mvwhline(local_win, y+long2-1, x, '-', long1+1);
	mvwvline(local_win, y, x, '|', long2);
	mvwvline(local_win, y, x+long1+1, '|', long2);
	
}

void draw4(WINDOW *local_win){
	 rectangle(local_win, 3, 3, 42, 7);
	 mvwhline(local_win, 6, 6, '-', 38);
	 mvwhline(local_win, 12, 5, ' ', 2);
	 mvwhline(local_win, 12, 46, 'X', 2);
}



int main(){
int c;
WINDOW *wind;
//const char aa[2]={t}

initscr();
noecho();
cbreak();
keypad(wind,true);
wind = newwin(13,50,0,0);
wborder(wind,'|','|','-','-','-','-','-','-');
draw1(wind);

while(c!= 'q'){

if (nodelay(wind,TRUE)!= ERR)
		c = wgetch(wind);
}

 

endwin();
return (0);

}