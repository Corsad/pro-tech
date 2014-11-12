#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define MENULENGTH   4

char *menuList[] = 	{"1. New Game",
                        "2. High Scores",
                        "3. Credits",
                        "4. Exit",
                    	};

static int drawMenu(){
	int currentChoice = 1;
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

	while(((c = getch()) != 13) || (currentChoice != 4))
	{   switch(c)
	    {	case KEY_DOWN:
		        menu_driver(menu, REQ_DOWN_ITEM);
		        if(currentChoice < MENULENGTH){
                        currentChoice++;
                }
				break;
			case KEY_UP:
				menu_driver(menu, REQ_UP_ITEM);
				if(currentChoice > 1){
                        currentChoice--;
                }
				break;
			default:
				mvprintw(20, 1, "%i", currentChoice);
				break;
		}
	}	
	
	free_item(items[0]);
	free_item(items[1]);
	free_menu(menu);
	
	return currentChoice;
}

static void finish(int sig) {
    endwin();

    /* do your non-curses wrapup here, like freeing the memory allocated */


    exit(sig);
}

static void init_screen() {
	(void) signal(SIGINT, finish);
	initscr();
	(void) nonl();         
    (void) cbreak(); 
    (void) noecho();      
    keypad(stdscr, TRUE);   
    timeout(-1);
}

int main(int argc, char *argv[])
{
	init_screen();
	int currentChoice = drawMenu();


	switch(currentChoice){
		case 4:			
			finish(0);
		break;
	}
	
	endwin();
}