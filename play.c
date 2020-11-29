#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
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
