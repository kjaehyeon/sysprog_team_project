#include <stdio.h>
#include <curses.h>
#include <string.h>
#define BUFFER_SIZE 256
void print_gameover();
void save_score(int score);
void open_file();
int main(void){
	int score = 1000;
	initscr();	
	print_gameover();
	open_file();
	refresh();
	getch();
	endwin();
}

void open_file(){
	char buffer[BUFFER_SIZE+1];
	FILE* fp;
	int cnt = 0;
	move(25,COLS/2);
	addstr("SCORE");
	const int max = 1024;
	char *pLine;
	char line[max];
	fp = fopen("test.txt", "r");

	while(!feof(fp)){
		pLine = fgets(line,max,fp);
		move(30+cnt,COLS/2);
		addstr(pLine);
		cnt +=1;
	}
	fclose(fp);
	
}	

void print_gameover(){
        clear();
        move(10,COLS/2-40);
        addstr(" #####     #    #     # #######    ####### #     # ####### ###### ");
        move(11,COLS/2-40);
        addstr("#     #   # #   ##   ## #          #     # #     # #       #     #");
        move(12,COLS/2-40);
        addstr("#        #   #  # # # # #          #     # #     # #       #     #");
        move(13,COLS/2-40);
        addstr("#  #### #     # #  #  # #####      #     # #     # #####   ######");
        move(14,COLS/2-40);
        addstr("#     # ####### #     # #          #     #  #   #  #       #   # ");
        move(15,COLS/2-40);
        addstr("#     # #     # #     # #          #     #   # #   #       #    #");
        move(16,COLS/2-40);
        addstr(" #####  #     # #     # #######    #######    #    ####### #     # ");
}
