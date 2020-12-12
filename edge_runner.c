#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "edge_runner.h"

enum state { initial, in_play, help};//enum for store program state

int main(void){
	
	printf("\033[8;50;120t");// set terminal size col = 120, row = 50

	char ch;
	int play_retVal = 0; 
	enum state cur_state = initial;
	
	initscr();
	crmode();
	noecho();
	startWin();

	while(1){
		ch = getch();
		if(cur_state != in_play){	
			if(ch == 'h' &&	cur_state == initial){
				cur_state = help;
				helpWin();
			}
			if(ch == 's' && cur_state == initial){	
				cur_state = in_play;
				play();
		
			//this code will activate after implementing play();
				/*play_retVal = play();
				if(play_retVal == 1){
					cur_state = start;
					startWin();
				}else exit(0);*/
			
			}
			if(ch == 'b' && cur_state == help){
				cur_state = initial;
				startWin();
			}
		
			//test code from here
			if(ch == 'b' && cur_state == in_play){
				cur_state = initial;
				startWin();
			}
			if(ch == 'e' && cur_state == initial){
				endwin();
				printf("exit\n");
				exit(0);
			}
			//to here
		}
	}
}
