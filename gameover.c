#include <stdio.h>
#include <curses.h>
#include <string.h>
#define BUFFER_SIZE 256
int rank[10];
void print_gameover();
void save_score(int score);
void open_file();
void gameover(){
	int score = 3000;
	initscr();	
	save_score(score);
	print_gameover();
	int i = 0;
	char s[10];
        char temp[10];
	char ra[10];
	move(24,COLS/2-3);
	addstr("Your score");
	move(25,COLS/2);
	sprintf(s,"%d",score);
	addstr(s);
	move(29,COLS/2-1);
	addstr("Ranking");
        for(i=0;i<9;i++){
                move(30+i,COLS/2);
                sprintf(temp,"%d ",rank[i]);
		sprintf(ra,"%d ",i+1);
		addstr(ra);
                addstr(temp);
        }
	refresh();
	endwin();
}

void save_score(int score){
	FILE* fp;
	int i=0;
	int tmp;
	fp = fopen("test.txt","r+");
	if(fp == 0){
		fp = fopen("test.txt","w+");
		fprintf(fp,"%d",score);
	}
	else{
	while(!feof(fp)){
		fscanf(fp,"%d", &rank[i++]);
	}
	if(rank[10] <score){
		rank[10] = score;
		for(i=9;i>=0;i--){
			if(rank[i]<score){
				tmp =rank[i];
				rank[i] = score;
				rank[i+1] = tmp;
			}
		}
	}

	fclose(fp);
	fp = fopen("test.txt","w+");
	i = 0;
	for(i=0;i<10;i++){
		fprintf(fp,"%d ",rank[i]);
	}
	}
	fclose(fp);
}
 
void print_gameover(int* rank){
        clear();
	int i = 0;
	char temp[10];
	
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
refresh();
endwin();
}
