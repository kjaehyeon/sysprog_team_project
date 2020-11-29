#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 50

void create_map();
void generate_random_map(int* map);
void create_left_map(void);
void create_bottom_map(void);
void create_top_map(void);
void create_right_map(void);

int bottom_map[SCREEN_WIDTH]= {1,};
int top_map[100] = {0,1,2,0,1,2,0,1,2,0,1,2,0,};
int left_map[100] = {1,2,}; 
int right_map[100] = {2,1,2,};

enum position {top,bottom,left,right,start};

int main(){

	enum position pos;
	pos = top; 
	initscr();
	clear();
	create_map(pos);
	addstr("play");
}

void generate_random_map(int* map){
	map[0] = 0;
	for(int i = 1 ; i < 100 ; i++){
		int random = rand() %3;
		map[i] = random;
		if(map[i-1] == map[i]){
			map[i] = 0;
		}
	}
}
	

void create_map(enum position pos){
	switch(pos){
		case start :
			create_top_map();
			create_right_map();
			create_left_map();
			create_bottom_map();
			break;
		case top :
			generate_random_map(right_map);
			create_top_map();
			create_right_map();
			create_left_map();
			create_bottom_map();
			break;
		case left :
			generate_random_map(top_map);
			create_top_map();
			create_right_map();
			create_left_map();
			create_bottom_map();
			break;
		case right:
			generate_random_map(bottom_map);
			create_top_map();
			create_right_map();
			create_left_map();
			create_bottom_map();
			break;
		case bottom:
			generate_random_map(left_map);
			create_left_map();
			create_top_map();
			create_right_map();
			create_bottom_map();
			break;
	}

	refresh();
	sleep(12342134);
	endwin();
}

void create_right_map(){
	for(int i = 0 ; i < SCREEN_HEIGHT ; i++){
		move(i , SCREEN_WIDTH);
		char temp[2];
		if(right_map[i] == 0){
			addstr("wall");
		}
		else if(right_map[i] == 1){
			addstr("ham");
		}	
	
	
		else{
			addstr("mon");
		}
	}
}
void create_left_map(){
		for(int i = 0; i < SCREEN_HEIGHT; i++){
		move(i,0);
		char temp[2];
		sprintf(temp, "%d",left_map[i]);
	
		addstr(temp);
	}
}

void create_top_map(){
	for(int i = 0 ; i < SCREEN_WIDTH ; i++){
		move(0, i);
		char temp[2];
		sprintf(temp , "%d", top_map[i]);
		addstr(temp);
	}
}

void create_bottom_map(){
	for(int i = 0 ; i < SCREEN_WIDTH ; i++){
		move(SCREEN_HEIGHT , i);
		char temp[2];	
		sprintf(temp, "%d", bottom_map[i]);
		addstr(temp);
	}
}
