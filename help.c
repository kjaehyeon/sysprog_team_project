#include<stdio.h>
#include<curses.h>
#include<string.h>

void help(){
	
	clear();
	int c;
	move(0,0);
	addstr("press 'b' to go startpage");
	move(10,COLS/2-30);
	addstr("#     # ####### #       ###### ");
	move(11,COLS/2-30);
	addstr("#     # #       #       #     # ");
	move(12,COLS/2-30);
	addstr("####### #####   #       ###### ");
	move(13,COLS/2-30);
	addstr("#     # #       #       #     ");
	move(14,COLS/2-30);
	addstr("#     # ####### ####### # ");
	move(23,0);
	addstr("Your character should survive running through edge of console.");
	move(24,0);
	addstr("Obstacles and Monsters are randomly spawn.");
	move(25,0);
	addstr("*Jump - space bar");
	move(26,0);
	addstr("*Attack - a");
	move(27,0);
	addstr("*Slide - s");

	refresh();

	endwin();
}
