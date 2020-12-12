#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/time.h>
#include <signal.h>
#include "edge_runner.h"

int **totalmap;

extern int bottom_map[];
extern int top_map[];
extern int left_map[];
extern int right_map[];

int cur_score = 0;
//enum position {top, bottom, left, right, start}; //enum for runner's positon 
enum action {attack, jump, slide, run};
typedef struct _location{
	int x;
	int y;
}location;
typedef struct _Runner{
	enum position pos;
	enum action act;
	location loc;
}Runner;

location *direction;
Runner* runner;

int set_ticker(int);
void run_runner(Runner*);
void attack_runner(Runner*);
void slide_runner(Runner*);
void draw_runner(Runner*);
void checking();
void up(){
	if(runner->pos == bottom)
		direction->y = -1;
	if(runner->pos == right)
		direction->x = -2;
	if(runner->pos == top)
		direction->y = 1;
	if(runner->pos == left)
		direction->x = 2;	
}
void forward(){
	if(runner->pos == bottom)
		direction->y = 0;
	if(runner->pos == right)
		direction->x = 0;
	if(runner->pos == top)
		direction->y = 0;
	if(runner->pos == left)
		direction->x = 0;
}
void down(){
	if(runner->pos == bottom)
                 direction->y = 1;
        if(runner->pos == right)
                 direction->x = 2;
        if(runner->pos == top)
                 direction->y = -1;
        if(runner->pos == left)
                 direction->x = -2;
}
void jumping(){
	set_ticker(0);
	runner->act = jump;
	up();
	draw_runner(runner);
	checking();
	usleep(50000);
	draw_runner(runner);
	checking();
	usleep(50000);
	draw_runner(runner);
	checking();
	usleep(50000);
	forward();
	draw_runner(runner);
	checking();
	usleep(50000);
	draw_runner(runner);
	checking();
	usleep(50000);
	draw_runner(runner);
	checking();
	usleep(50000);
	down();
	draw_runner(runner);
	checking();
	usleep(50000);	
	draw_runner(runner);
	checking();
	usleep(50000);
	draw_runner(runner);
	checking();
	usleep(50000);
	forward();
	checking();
	runner->act = run;
	set_ticker(50);
}
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
	if(runner->act == slide){
		mvaddstr(runner->loc.y,runner->loc.x," ");
	}
	else{
		if(runner->pos == top){
			mvaddstr(runner->loc.y, runner->loc.x, "   ");
			mvaddstr(runner->loc.y+1, runner->loc.x,"   ");
			mvaddstr(runner->loc.y+2, runner->loc.x,"   ");
			mvaddstr(runner->loc.y+3, runner->loc.x,"   ");
			mvaddstr(runner->loc.y+4, runner->loc.x,"   ");
		}
		if(runner->pos == bottom){
			mvaddstr(runner->loc.y, runner->loc.x,"   ");
			mvaddstr(runner->loc.y-1, runner->loc.x,"   ");
			mvaddstr(runner->loc.y-2, runner->loc.x,"   ");
			mvaddstr(runner->loc.y-3, runner->loc.x,"   ");
			mvaddstr(runner->loc.y-4, runner->loc.x,"   ");
		}
		if(runner->pos == right){
			mvaddstr(runner->loc.y,runner->loc.x-7,"        ");
		}
		if(runner->pos == left){
			mvaddstr(runner->loc.y,runner->loc.x,"          ");
		}
	}	
	runner->loc.x += direction->x;
	runner->loc.y += direction->y;
	
	if(runner->loc.x >= COLS){
		runner->loc.x = COLS-1;
		runner->act = run;
		set_ticker(50);
	}
	if(runner->loc.x < 0){
		runner->loc.x = 1;
		runner->act = run;
		set_ticker(50);
	}
	if(runner->loc.y > LINES-1){
		runner->loc.y = LINES-1;
		runner->act = run;
		set_ticker(50);
	}
	if(runner->loc.y < 0){
		runner->loc.y = 1;
		runner->act = run;
		set_ticker(50);
	}

	switch(runner->act){
		case run:
			run_runner(runner);
			break;
		case attack:
			attack_runner(runner);
			break;
		case slide:
			slide_runner(runner);
			break;
		case jump:
			run_runner(runner);
			break;
	}	

}
void checking(){
	int tmp;
	if(runner->pos == top){
		tmp = totalmap[top][runner->loc.x];
		if(tmp != 0){
			switch(tmp){
				case 1:
					if(runner->act != attack){
						set_ticker(0);
						gameover(cur_score);
					}
					break;
				case 2:
					if(runner->loc.y < 3){
						set_ticker(0);
						gameover(cur_score);
					}
					break;
				case 3:
					if(runner->act != slide){
						set_ticker(0);
						gameover(cur_score);
					}
					break;
			}
		}		
	}else if(runner->pos == bottom){
		tmp = totalmap[bottom][runner->loc.x];
		if(tmp != 0){
			switch(tmp){
				case 1:
					if(runner->act != attack){
						set_ticker(0);
						gameover(cur_score);
					}	
					break;
				case 2:
					if(runner->loc.y >= LINES-3){
						set_ticker(0);
						gameover(cur_score);
					}
					break;
				case 3:
					if(runner->act != slide){
						set_ticker(0);
						gameover(cur_score);
					}	
					break;	
			}
		}
	}else if(runner->pos == right){
		tmp = totalmap[right][runner->loc.y];
		if( tmp != 0){
			switch(tmp){
				case 1:
					break;
				case 2:
					if(runner->loc.x >= COLS-4){
						set_ticker(0);
						gameover(cur_score);
					}
					break;
				case 3:
					if(runner->act != slide){
						set_ticker(0);
						gameover(cur_score);
					}
					break;
			}
		}
	}else{
		tmp = totalmap[left][runner->loc.y];
		if(tmp != 0){
			switch(tmp){
				case 1:
					break;
				case 2:
					if(runner->loc.x < 4){
						set_ticker(0);
						gameover(cur_score);
					}
					break;
				case 3:
					if(runner->act != slide){
						set_ticker(0);
						gameover(cur_score);
					}
					break;
			}
		}
	}


}
void run_runner(Runner* runner){
	if(runner->pos == top){
		mvaddstr(runner->loc.y, runner->loc.x,"Z");
		mvaddstr(runner->loc.y+1, runner->loc.x,"o");
	}
	if(runner->pos == right){
		mvaddstr(runner->loc.y, runner->loc.x-2,"o-<");
	}
	if(runner->pos == left){
		mvaddstr(runner->loc.y, runner->loc.x,">-o");
	}
	if(runner->pos == bottom){
		mvaddstr(runner->loc.y,runner->loc.x,"Z");
		mvaddstr(runner->loc.y-1,runner->loc.x,"o");
	}
	refresh();

}
void attack_runner(Runner* runner){
	if(runner->pos == top){
		mvaddstr(runner->loc.y, runner->loc.x," Z");
		mvaddstr(runner->loc.y+1, runner->loc.x-1,"((o");
	}
	if(runner->pos == right){
		mvaddstr(runner->loc.y-1, runner->loc.x-2,"^  ");
		mvaddstr(runner->loc.y, runner->loc.x-2,"o-<");
	}
	if(runner->pos == left){
		mvaddstr(runner->loc.y, runner->loc.x,">-o");
		mvaddstr(runner->loc.y+1, runner->loc.x,"  v");
	}
	if(runner->pos == bottom){
		mvaddstr(runner->loc.y,runner->loc.x,"Z");
		mvaddstr(runner->loc.y-1,runner->loc.x,"o))");
	}
	refresh();

}
void slide_runner(Runner* runner){
	mvaddch(runner->loc.y, runner->loc.x, 'o');
}
void handler(int signum){
	draw_runner(runner);
	checking();
	
	if(runner->pos == bottom  && runner->loc.x == COLS-1){
		runner->pos = right;
		direction->x = 0;
		direction->y = -1;
		update_map(runner->pos);
	}else if(runner->pos == right && runner->loc.y == 0){
		runner->pos = top;
		direction->x = -1;
		direction->y = 0;
		update_map(runner->pos);
	}else if(runner->pos == top && runner->loc.x == 0){
		runner->pos = left;
		direction->x = 0;
		direction->y = 1;
		update_map(runner->pos);
	}else if(runner->pos == left && runner->loc.y == LINES-1){
		runner->pos = bottom;
		direction->x = 1;
		direction->y = 0;
		update_map(runner->pos);
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
	char c;
	totalmap = (int**)malloc(sizeof(int*) * 4);
	
	clear();
	
	signal(SIGALRM, handler);
	direction = (location*)malloc(sizeof(location));
       	direction->x = 1;
	direction->y = 0; // initialize direction	
	runner = (Runner*)malloc(sizeof(Runner));
	runner->pos = bottom;
	runner->loc.x = 1;
	runner->loc.y = LINES-1;// initialize runner
	runner->act = run;

	update_map(start);

	totalmap[bottom] = (int*)malloc(sizeof(int) * 120);
	totalmap[top] = (int*)malloc(sizeof(int) * 120);
	totalmap[right] = (int*)malloc(sizeof(int) * 50);
	totalmap[left] = (int*)malloc(sizeof(int) * 50);

	totalmap[bottom] = bottom_map;
	totalmap[right] = right_map;
	totalmap[top] = top_map;
	totalmap[left] = left_map;
	


	mvaddstr(runner->loc.y, runner->loc.x, "o");
	set_ticker(50);
	while(1){
		c = getch();
		if(c == ' '){
			jumping();
		}
		if(c == 'a'){
			if(runner->pos == top){
                                mvaddstr(runner->loc.y, runner->loc.x-1,"  ");
				mvaddstr(runner->loc.y-1, runner->loc.x-1,"  ");
				mvaddstr(runner->loc.y-2, runner->loc.x-1,"  ");
			}
                        else if(runner->pos == bottom){
                                mvaddstr(runner->loc.y, runner->loc.x+1,"  ");
				mvaddstr(runner->loc.y+1, runner->loc.x+1,"  ");
				mvaddstr(runner->loc.y+2, runner->loc.x+1,"  ");
			}
			set_ticker(0);
			runner->act = attack;
			draw_runner(runner);
			checking();
			usleep(50000);
			draw_runner(runner);
			checking();
			usleep(50000);
			draw_runner(runner);
			checking();
			usleep(50000);
			draw_runner(runner);
			checking();
			usleep(50000);
			draw_runner(runner);
			checking();
			usleep(50000);
			draw_runner(runner);
                        checking();
                        usleep(50000);
			draw_runner(runner);
                        checking();
                        usleep(50000);
			runner->act = run;
			set_ticker(50);
			//attack
		}	
		if(c == 's'){
			if(runner->pos == top)
				mvaddstr(runner->loc.y+1, runner->loc.x," ");
			else if(runner->pos == bottom)
				mvaddstr(runner->loc.y-1, runner->loc.x," ");
			else if(runner->pos == right)
				mvaddstr(runner->loc.y, runner->loc.x-2, "  ");
			else
				mvaddstr(runner->loc.y, runner->loc.x+1, "  ");

			set_ticker(0);
			runner->act = slide;
			draw_runner(runner);
			checking();
			usleep(25000);
			draw_runner(runner);
			checking();
			usleep(25000);
			draw_runner(runner);
			checking();
			usleep(25000);
			draw_runner(runner);
			checking();
			usleep(25000);
			draw_runner(runner);
			checking();
			usleep(25000);
			draw_runner(runner);
			checking();
			usleep(25000);
			draw_runner(runner);
			checking();
			usleep(25000);
			draw_runner(runner);
			checking();
			usleep(25000);
			draw_runner(runner);
			checking();
			runner->act = run;
			set_ticker(50);
			//slide
		}
		if(c == 'e'){
			set_ticker(0);
			gameover(cur_score);	
		}
	}
	refresh();

}
