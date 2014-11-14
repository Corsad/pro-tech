#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <assert.h>

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
}
