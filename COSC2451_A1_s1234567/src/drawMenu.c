#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include <menu.h>

#include "drawMenu.h"
#include "Simplify.h"
#include "highScore.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define ROW1	4
#define ROW2	6
#define ROW3	8


int main(int argc, char *argv[])
{
	init_screen();
	int currentChoice = 1;
	drawMenu(&currentChoice);
	
	endwin();
}

static void doChoice(int * currentChoice){
	mvprintw(20,20,"%i\n", currentChoice);
	switch(*currentChoice){
		case 1:			
			clear();
			drawBoardMenu(1);
			clear();
			*currentChoice = 1;
			drawMenu(currentChoice);
		break;
		case 2:
			clear();
			drawBoardMenu(2);
			clear();
			*currentChoice = 1;
			drawMenu(currentChoice);
		break;
		case 3:
			clear();
			printCredit();
			clear();
			*currentChoice = 1;
			drawMenu(currentChoice);
		break;
		case 4:			
			finish(0);
		break;
		case 5:
			clear();
			testHighScore();
			clear();
			*currentChoice = 1;
			drawMenu(currentChoice);
		break;
	}
}

static void drawMenu(int * currentChoice){	
	char *menuList[] = 	{"1. New Game",
                        "2. High Scores",
                        "3. Credits",
                        "4. Exit"
                    	};

	ITEM **items;
	int c;				
	MENU *menu;
	int menu_choices, i;
	ITEM *cur_item;
	menu_choices = ARRAY_SIZE(menuList);
	items = (ITEM **)calloc(menu_choices + 1, sizeof(ITEM *));

	for(i = 0; i < menu_choices; ++i)
	        items[i] = new_item(" ", menuList[i]);
	

	items[menu_choices] = (ITEM *)NULL;

	menu = new_menu((ITEM **)items);
	post_menu(menu);
	refresh();

	while(((c = getch()) != 13))
	{   switch(c)
	    {	case KEY_DOWN:
		        menu_driver(menu, REQ_DOWN_ITEM);
		        if(*currentChoice < menu_choices){
                        *currentChoice += 1;
                }
				break;
			case KEY_UP:
				menu_driver(menu, REQ_UP_ITEM);
				if(*currentChoice > 1){
                        *currentChoice -= 1;
                }
				break;
		}
	}	
	
	doChoice(currentChoice);

	unpost_menu(menu);
	free_menu(menu);
	for(i = 0; i < menu_choices; ++i)
	        free_item(items[i]);

	free_item(cur_item);
	free(items);
}

static void doBoardChoice(int modeChoice, int boardChoice){
	mvprintw(20,20,"%i\n", boardChoice);
	clear();
	switch(modeChoice) {
		case 1:
			switch(boardChoice){
				case 1:		
					playGame(ROW1,ROW1);
					break;
				case 2:
					playGame(ROW2,ROW2);
					break;
				case 3:	
					playGame(ROW3,ROW3);
				break;
			}
		break;
		case 2:
			switch(boardChoice){
				case 1:		
					printHighscore();
					break;
				case 2:
					printHighscore();
					break;
				case 3:	
					printHighscore();
				break;
			}
		break;
	}
	
	clear();
}

static void drawBoardMenu(int modeChoice){	
	int boardChoice = 1 ;
	char *menuList[] = 	{"1.4x4",
                        "2.6x6",
                        "3.8x8",
                        "4. Back to menu"
                    	};

	ITEM **items;
	int c;				
	MENU *menu;
	int menu_choices, i;
	ITEM *cur_item;
	menu_choices = ARRAY_SIZE(menuList);
	items = (ITEM **)calloc(menu_choices + 1, sizeof(ITEM *));

	for(i = 0; i < menu_choices; ++i)
	        items[i] = new_item(" ", menuList[i]);
	

	items[menu_choices] = (ITEM *)NULL;

	menu = new_menu((ITEM **)items);
	post_menu(menu);
	refresh();

	while(((c = getch()) != 13))
	{   switch(c)
	    {	case KEY_DOWN:
		        menu_driver(menu, REQ_DOWN_ITEM);
		        if(boardChoice <= menu_choices){
                        boardChoice += 1;
                }
				break;
			case KEY_UP:
				menu_driver(menu, REQ_UP_ITEM);
				if(boardChoice > 1){
                        boardChoice -= 1;
                }
				break;
		}
	}	

	doBoardChoice(modeChoice,boardChoice);

	unpost_menu(menu);
	free_menu(menu);
	for(i = 0; i < menu_choices; ++i)
	        free_item(items[i]);

	//free_item(cur_item);
	free(items);	
}

static void finish(int sig) {
    endwin();

    /* do your non-curses wrapup here, like freeing the memory allocated */


    exit(sig);
}

static void init_screen() {
	(void) signal(SIGINT, finish);
	(void) initscr(); 
	(void) nonl();         
    (void) cbreak(); 
    (void) noecho();      
    keypad(stdscr, TRUE);   
    timeout(-1);
    start_color();
    defaultColor();
    definePair();
}

void defaultColor(){
	init_color(COLOR_RED, 1000, 0, 0);
	init_color(COLOR_GREEN, 0, 1000, 0);
	init_color(COLOR_YELLOW, 1000, 1000, 0);
	init_color(COLOR_BLUE, 0, 0, 1000);
	init_color(COLOR_MAGENTA, 1000, 0, 1000);
	init_color(COLOR_CYAN, 0, 1000, 1000);
	init_color(COLOR_WHITE, 0, 0, 0);
	init_color(COLOR_BLACK, 1000, 1000, 1000);
}

void definePair(){
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
}

static void printCredit(){
	mvprintw(0, 0, "DANG KIM KHANH\tS3372771");
	mvprintw(1, 0, "LE THIEN HUY\tS3425476");

	mvprintw(3, 0, "Press \'q\' to go back to menu.");

	int c;
	while(((c = getch()) != 'q')){		
	}
}