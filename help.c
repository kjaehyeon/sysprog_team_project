#include<stdio.h>
#include<curses.h>
#include<string.h>
int main(){
	initscr();
	int c;
	move(0,COLS-30);
	addstr("press 'b' to go startpage");
	move(2,COLS/2-30);
	addstr("#     # ####### #       ###### ");
	move(3,COLS/2-30);
	addstr("#     # #       #       #     # ");
	move(4,COLS/2-30);
	addstr("####### #####   #       ###### ");
	move(5,COLS/2-30);
	addstr("#     # #       #       #     ");
	move(6,COLS/2-30);
	addstr("#     # ####### ####### # ");
	move(23,40);
	addstr("Your character should survive running through edge of console.");
	move(24,50);
	addstr("Obstacles and Monsters are randomly spawn.");
	move(30,COLS/2-35);
	addstr(" * ");
	move(31,COLS/2-35);
	addstr("***");
	move(32,COLS/2-35);
	addstr(" | "); 
	move(31,COLS/2-30);
	addstr("Jump -press 'space bar' when you meet tree");
	move(35,COLS/2-36);
	addstr(" o o ");
	move(36,COLS/2-36);
	addstr("-(@)-");
	move(37,COLS/2-36);
	addstr(" | | ");
	move(36,COLS/2-29);
	addstr("Attack - press 'a' when you meet monster");
	move(40,COLS/2-35);
	addstr("====");
	move(41,COLS/2-35);
	addstr("|  |");
	move(42,COLS/2-35);
	addstr("|  |");
	move(43,COLS/2-35);
	addstr("|  |");
	move(41,COLS/2-30);
	addstr("Slide - press 's' when you meet hurdle");
	refresh();
	getch();
	endwin();

}
