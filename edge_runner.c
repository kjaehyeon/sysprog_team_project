#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>

#include "edge_runner.h"
enum state { start, in_play, help};//enum for store program state

void helpWin();
int play();


int main(void){
	
	printf("\033[8;50;100t");// set terminal size col = 100, row = 50

	char ch;
	int play_retVal = 0; 
	enum state cur_state = start;
	
	int flag = fcntl(0, F_GETFL);
	flag |= O_NONBLOCK;
	fcntl(0, F_SETFL, flag);

	initscr();
	crmode();
	noecho();
	startWin();

	while(1){
		ch = getch();
		
		if(ch == 'h' &&	cur_state == start){
			helpWin();
			cur_state = help;
		}
		if(ch == 's' && cur_state == start){	
			cur_state = in_play;
			play();
		
		//this code will activate after implementing play();
		/*	play_retVal = play();

			if(play_retVal == 1){
				cur_state = start;
				startWin();
			}else exit(0);*/
			
		}
		if(ch == 'b' && cur_state == help){
			startWin();
			cur_state = start;
		}
		
		//test code from here
		if(ch == 'b' && cur_state == in_play){
			startWin();
			cur_state = start;
		}
		if(ch == 'e' && cur_state == start){
			endwin();
			printf("exit\n");
			exit(0);
		}
		//to here

	}
}
