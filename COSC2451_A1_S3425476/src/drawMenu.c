#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include <menu.h>
#include <unistd.h>

#include "drawMenu.h"
#include "board.h"
#include "highScore.h"
#include "khanhAI.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define ROW1	4
#define ROW2	6
#define ROW3	8

int playerMode = 1;
int AISelected[2];
int (* AIFuncs[2])(int **, int, int) = {&getHighestScore};

int main(int argc, char *argv[])
{
	init_screen();
	int currentChoice = 1;
	drawMenu(&currentChoice);
	
	endwin();
}

void doChoice(int * currentChoice){
	mvprintw(20,20,"%i\n", currentChoice);
	switch(*currentChoice){
		case 1:
			clear();
			switch(playerMode){
				case 1:
					drawBoardMenu(*currentChoice);
					break;
				case 2:
					playGameAI(ROW1,ROW1, AIFuncs[AISelected[0]]);
					break;
				case 3:
					playGame2Player(ROW1,ROW1);
					break;
				case 4:
					playGamePlayerVsAI(ROW1,ROW1, AIFuncs[AISelected[0]]);
					break;
				case 5:
					playGameAIVsAI(ROW1,ROW1, AIFuncs[AISelected[0]], AIFuncs[AISelected[1]]);
					break;
			}
			clear();
			*currentChoice = 1;
			drawMenu(currentChoice);
		case 2:		
			clear();
			drawBoardMenu(*currentChoice);
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
			clear();
			PlayerSelectionMenu();
			clear();
			*currentChoice = 1;
			drawMenu(currentChoice);
		case 5:	
			clear();
			printQuit(currentChoice, ' ');	
			finish(0);
		break;
	}
}

void drawMenu(int * currentChoice){	
	char *menuList[] = 	{"1. New Game",
                        "2. High Scores",
                        "3. Credits",
                        "4. Player Mode Selection",
                        "5. Exit"
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
			case 'n':
			case 'N':
				*currentChoice=1;
				goto JUMP;
			case 'h':
			case 'H':
				*currentChoice=2;
				goto JUMP;
			case 'c':
			case 'C':
				*currentChoice=3;
				goto JUMP;
			case 'p':
			case 'P':
				*currentChoice=4;
				goto JUMP;
			case 'e':
			case 'E':
				*currentChoice=5;
				goto JUMP;
		}
	}	
	
JUMP:	doChoice(currentChoice);

	unpost_menu(menu);
	free_menu(menu);
	for(i = 0; i < menu_choices; ++i)
	        free_item(items[i]);

	free_item(cur_item);
	free(items);
}

void doBoardChoice(int modeChoice, int boardChoice){
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
					printHighscore(ROW1,ROW1);
					break;
				case 2:
					printHighscore(ROW2,ROW2);
					break;
				case 3:	
					printHighscore(ROW3,ROW3);
				break;
			}
		break;
	}
	
	clear();
}

void drawBoardMenu(int modeChoice){	
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

void PlayerSelectionMenu(){	
	int boardChoice = 1 ;
	char *menuList[] = 	{"1. 1 Player",
						"2. AI",
                        "3. 2 Player",
                        "4. 1 Player vs AI",
                        "5. AI vs AI",
                        "6. Back to menu"
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

	switch(boardChoice){
		case 1:
			playerMode = 1;
			break;
		case 2:
			playerMode = 2;
			selectAI(1);
			break;
		case 3:
			playerMode = 3;
			break;
		case 4:
			playerMode = 4;
			selectAI(1);
			break;
		case 5:
			playerMode = 5;
			selectAI(2);
			break;
	}

	unpost_menu(menu);
	free_menu(menu);
	for(i = 0; i < menu_choices; ++i)
	        free_item(items[i]);

	//free_item(cur_item);
	free(items);	
}

void selectAI(int amountOfPlayer){
	clear();
	int boardChoice = 1 ;
	char *menuList[amountOfPlayer + 1];
	switch(amountOfPlayer){
		case 1:
			menuList[0] = "1. Khanh AI";
			menuList[1] = "2. Huy AI";            
		break;
		case 2:
			menuList[0] = "1. Khanh AI vs Khanh AI";
			menuList[1] = "2. Khanh AI vs Huy AI";
			menuList[2] = "3. Huy AI vs Huy AI";            
		break;
	}
	

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
	switch(amountOfPlayer){
		case 1:
			switch(boardChoice){
				case 1:
					AISelected[0] = 0;

					break;
				case 2:
					AISelected[0] = 1;
					;
					break;
			}
		break;
		case 2:
			switch(boardChoice){
				case 1:
					AISelected[0] = 0;
					AISelected[1] = 0;
					break;
				case 2:
					AISelected[0] = 0;
					AISelected[1] = 1;
					;
					break;
				case 3:
					AISelected[1] = 1;
					AISelected[1] = 1;
					break;
			}
		break;
	}
	

	unpost_menu(menu);
	free_menu(menu);
	for(i = 0; i < menu_choices; ++i)
	        free_item(items[i]);

	//free_item(cur_item);
	free(items);	
}

void finish(int sig) {
    endwin();

    /* do your non-curses wrapup here, like freeing the memory allocated */


    exit(sig);
}

void init_screen() {
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

void printCredit(){
	mvprintw(0, 0, "DANG KIM KHANH\tS3372771");
	mvprintw(1, 0, "LE THIEN HUY\tS3425476");

	mvprintw(3, 0, "Press \'q\' to go back to menu.");

	int c;
	while(((c = getch()) != 'q')){		
	}
}

void printQuit(int * currentChoice, char i){
	mvprintw(0, 0, "Are you sure you want to quit? ");
	mvprintw(0, 31, "%c", i);
	int c = getch();
	
	if(c == 'y'){
		mvprintw(0, 31, "%c", c);
		mvprintw(1, 0, "Thanks for playing\n");
		refresh();
		sleep(1);
	} else if (c == 'n'){
		clear();
		*currentChoice = 1;
		drawMenu(currentChoice);
	} else {
		printQuit(currentChoice, c);
	}
}