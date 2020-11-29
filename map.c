#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
<<<<<<< HEAD
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
=======
#include <sys/time.h>
#include <signal.h>

int cur_score = 0;
enum position {top, bottom, left, right, start}; //enum for runner's positon 
typedef struct _location{
	int x;
	int y;
}location;
typedef struct _Runner{
	enum position pos;
	location loc;
}Runner;

location *direction;
Runner* runner;

void draw_score(){
	char score[10];
	sprintf(score, "%d",cur_score);
	mvaddstr(LINES/2, COLS/2-1, "SCORE");
	mvaddstr(LINES/2 +1, COLS/2,score);
	refresh();
}
void draw_runner(Runner* runner){
	cur_score++;
	draw_score();
	mvaddstr(runner->loc.y, runner->loc.x, " ");
	runner->loc.x += direction->x;
	runner->loc.y += direction->y;
	mvaddstr(runner->loc.y, runner->loc.x, "o");
	refresh();
}
void handler(int signum){
	draw_runner(runner);
	if(runner->pos == bottom  && runner->loc.x == COLS-1){
		runner->pos = right;
		direction->x = 0;
		direction->y = -1;
	}else if(runner->pos == right && runner->loc.y == 0){
		runner->pos = top;
		direction->x = -1;
		direction->y = 0;
	}else if(runner->pos == top && runner->loc.x == 0){
		runner->pos = left;
		direction->x = 0;
		direction->y = 1;
	}else if(runner->pos == left && runner->loc.y == LINES-1){
		runner->pos = bottom;
		direction->x = 1;
		direction->y = 0;
	}
}
int set_ticker(int n_msecs){
	struct itimerval new_timeset;
	long n_sec, n_usecs;

	n_sec = n_msecs / 1000;
	n_usecs = (n_msecs % 1000) * 1000L;

	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_usecs;
	new_timeset.it_value.tv_sec = n_sec;
	new_timeset.it_value.tv_usec = n_usecs;

	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

void play(){
	//initscr();
	//crmode();
	//noecho();
	clear();
	
	char c;

	signal(SIGALRM, handler);
	direction = (location*)malloc(sizeof(location));
       	direction->x = 1;
	direction->y = 0; // initialize direction	
	runner = (Runner*)malloc(sizeof(Runner));
	runner->pos = bottom;
	runner->loc.x = 1;
	runner->loc.y = LINES-1;// initialize runner

	mvaddstr(runner->loc.y, runner->loc.x, "o");
	set_ticker(50);
	refresh();
	c = getch();
	if(c == 'e') endwin();

}
//int main(void){
//	play();
//}
>>>>>>> 735c8f3042b8848b46efd3ebadfe67c0892f7c65
