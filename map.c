#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include "edge_runner.h"

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 50


/*enum position {bottom,right,top,left,start};*/

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



void generate_random_map(enum position pos, int map[]){
	// 1 : mosnter 2: tree 3: hurdle
	int arrlen;
	srand(time(NULL));
	
	if(pos == top || pos == bottom) arrlen = SCREEN_HEIGHT;
	else arrlen = SCREEN_WIDTH;

	for(int i = 0; i < arrlen; i++)
		map[i] = 0;
	
	for(int i = 0; i < arrlen; i++){
		int random = rand()%4;
		if(i > 10  && i < arrlen -10){
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
			generate_random_map(top,right_map);	
			generate_random_map(left,top_map);
			generate_random_map(right,bottom_map);
			generate_random_map(bottom,left_map);
			create_bottom_map();
			create_right_map();
			create_top_map();
			create_left_map();
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

void create_left_map(){
	char tmp;
	for(int i=0;i<SCREEN_HEIGHT;i++){
		mvaddstr(i,0,"    ");
	}
	for(int i = 0 ; i < SCREEN_HEIGHT ; i++){
		tmp = left_map[i] + '0';
		if(tmp == '2')
			mvaddstr(i, 0 ,"-++");
		else if(tmp == '3'){
			mvaddstr(i, 0, "  |");
		}
	}
}
void create_right_map(){
	char tmp;
	for(int i=0;i<SCREEN_HEIGHT;i++){
		mvaddstr(i,COLS-4,"    ");
	}
	for(int i = 0 ; i < SCREEN_HEIGHT ; i++){
		tmp = right_map[i] + '0';
		if(tmp == '2')
			mvaddstr(i,COLS-3 , "++-");
		else if(tmp == '3'){
			mvaddstr(i,COLS-3,"|   ");
		}

	}

}

void create_top_map(){
	char tmp;
	for(int i = 0 ; i < SCREEN_WIDTH ; i++){
		mvaddstr(0,i,"     ");
		mvaddstr(1,i,"     ");
		mvaddstr(2,i,"     ");
	}
	for(int i =0;i<SCREEN_WIDTH;i++){
		tmp = top_map[i]+'0';
		if(tmp == '1'){
			mvaddstr(0, i, " | / ");
			mvaddstr(1, i,"-(@)-");
			mvaddstr(2, i," @ @ ");
		}
		if(tmp == '2'){
			mvaddstr(0,i," | ");
			mvaddstr(1,i,"***");
			mvaddstr(2,i," * ");
		}
		if(tmp == '3'){
			mvaddstr(1,i,"=");
		}
	}
}

void create_bottom_map(){
	char tmp;
	for(int i=0;i<SCREEN_WIDTH;i++){
		mvaddstr(LINES-1,i,"    ");
		mvaddstr(LINES-2,i,"    ");
                mvaddstr(LINES -3,i,"    ");
	}
	for(int i = 0 ; i < SCREEN_WIDTH ; i++){
		tmp = bottom_map[i] + '0';
		if(tmp == '1'){
			mvaddstr(LINES-1, i," / | ");
			mvaddstr(LINES-2, i,"-(@)-");
			mvaddstr(LINES-3, i," @ @ ");
		}
		if(tmp == '2'){
			mvaddstr(LINES-1, i, "  |  ");
			mvaddstr(LINES-2, i," ***");
			mvaddstr(LINES-3, i,"  *  ");
		}
		if(tmp == '3'){
			mvaddstr(LINES-2,i,"=");
		}
	}
}

