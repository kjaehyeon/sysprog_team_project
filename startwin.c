#include <stdio.h>
#include <curses.h>

void startWin(){
	clear();
	move(10,COLS/2-40);
	addstr("####### ######   #####  #######    ######  #     # #     # #     # ####### ######");
	move(11,COLS/2-40);
	addstr("#       #     # #     # #          #     # #     # ##    # ##    # #       #     #");
	move(12,COLS/2-40);
	addstr("#       #     # #       #          #     # #     # # #   # # #   # #       #     #");
	move(13, COLS/2-40);
	addstr("#####   #     # #  #### #####      ######  #     # #  #  # #  #  # #####   ######");
	move(14,COLS/2-40);
	addstr("#       #     # #     # #          #   #   #     # #   # # #   # # #       #   #");
	move(15,COLS/2-40);
	addstr("#       #     # #     # #          #    #  #     # #    ## #    ## #       #    #");
	move(16,COLS/2-40);
	addstr("####### ######   #####  #######    #     #  #####  #     # #     # ####### #     # ");
	move(20,COLS/2-30);
	addstr("     		      ,////,");
	move(21, COLS/2-30);
	addstr("                        /// 6|");
        move(22, COLS/2-30);
	addstr("                        //  _|");
	move(23, COLS/2-30);
	addstr("                       _/_,-\'");
	move(24, COLS/2-30);
	addstr("                  _.-/\'/   \\   ,/;,");
	move(25, COLS/2-30);
	addstr("               ,-\' /\'  \\_  \\ / _/");
	move(26, COLS/2-30);
	addstr("               `\\ /     _/\\  ` /");
	move(27, COLS/2-30);
	addstr("                 |     /,  `\\_/");
	move(28, COLS/2-30);
	addstr("                 |     \\'");
	move(29, COLS/2-30);
	addstr(" pb  /\\_        /`      /\\");
	move(30, COLS/2-30);
	addstr("   /\' /_``--.__/\\  `,. /  \\");
	move(31, COLS/2-30);
	addstr("  |_/`  `-._     `\\/  `\\   `.");
	move(32, COLS/2-30);
	addstr("            `-.__/\'     `\\   |");
	move(33, COLS/2-30);
	addstr("                          `\\  \\");
	move(34, COLS/2-30);
	addstr("                            `\\ \\");
	move(35,COLS/2-30);
	addstr("                              \\_\\__");
	move(36,COLS/2-30);
	addstr("                               \\___)");
	move(LINES/2 + 13, COLS/2-10);
	addstr("**********************");
	move(LINES/2 + 14, COLS/2-10);
	addstr("Press S to Game Start");
	move(LINES/2 + 15, COLS/2-10);
	addstr("**********************");
	move(LINES/2 +16 , COLS/2-10);
	addstr("**********************");
	move(LINES/2 + 17, COLS/2-10);
	addstr("Press H for HELP");
	move(LINES/2 + 18, COLS/2-10);
	addstr("**********************");
	refresh();
}

