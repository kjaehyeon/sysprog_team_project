#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 50


enum position {bottom,right,top,left,start};

void update_map();
void generate_random_map(enum position, int[]);
void create_left_map(void);
void create_bottom_map(void);
void create_top_map(void);
void create_right_map(void);

int bottom_map[SCREEN_WIDTH]={0,}; 
int top_map[SCREEN_WIDTH] = {0,};
int left_map[SCREEN_HEIGHT] = {0,}; 
int right_map[SCREEN_HEIGHT] = {0,};


int main(){
	enum position pos;
	pos = start;
	initscr();
	clear();
	update_map(pos);
	sleep(1);
	for(int i = 0; i < 10; i++){
		update_map(i%4);
		sleep(1);
	}
	endwin();
}

void generate_random_map(enum position pos, int map[]){
	// 1 : moster 2: hurdle 3: tree
	int arrlen;
	srand(time(NULL));
	
	if(pos == top || pos == bottom) arrlen = SCREEN_HEIGHT;
	else arrlen = SCREEN_WIDTH;

	for(int i = 0; i < arrlen; i++)
		map[i] = 0;

	for(int i = 0; i < arrlen; i++){
		int random = rand()%4;
		if(i > 5 && i < arrlen -5){
			map[i] = random;
			switch(random){
				case 1:
					i+= 20+ rand()%4;
					break;
				case 2:
					i+= 20+ rand()%4;
					break;
				case 3:
					i+= 20 + rand()%4;
					break;
			}
		}
	}			
}
	

void update_map(enum position pos){
	switch(pos){
		case start :
			create_top_map();
			create_right_map();
			create_left_map();
			create_bottom_map();
			break;
		case top :
			generate_random_map(pos,right_map);
			create_right_map();
			break;
		case left :
			generate_random_map(pos,top_map);
			create_top_map();
			break;
		case right:
			generate_random_map(pos,bottom_map);
			create_bottom_map();
			break;
		case bottom:
			generate_random_map(pos,left_map);
			create_left_map();
			break;
	}

	refresh();
}

void create_right_map(){
	char tmp[2];
	for(int i = 0 ; i < SCREEN_HEIGHT ; i++){
		sprintf(tmp, "%d",right_map[i]);
		mvaddstr(i, COLS-1, tmp);
	}
}
void create_left_map(){
	char tmp[2];
	for(int i = 0 ; i < SCREEN_HEIGHT ; i++){
		sprintf(tmp, "%d",left_map[i]);
		mvaddstr(i,0 , tmp);
	}

}

void create_top_map(){
	char tmp[2];
	for(int i = 0 ; i < SCREEN_WIDTH ; i++){
		sprintf(tmp, "%d",top_map[i]);
		mvaddstr(0, i, tmp);
	}
}

void create_bottom_map(){
	char tmp[2];
	for(int i = 0 ; i < SCREEN_WIDTH ; i++){
		sprintf(tmp, "%d",bottom_map[i]);
		mvaddstr(LINES-1, i, tmp);
	}
}

