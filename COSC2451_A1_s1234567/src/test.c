#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <assert.h>

#define DEFAULT_BOARD_SIZE 4
#define DEAFULT_GOAL 2048

#define COLOR_BACKGROUND    0
#define COLOR_2             1            
#define COLOR_4             2
#define COLOR_8             3
#define COLOR_16            4
#define COLOR_TEXT          7

int board_size = DEFAULT_BOARD_SIZE;

unsigned int **board_p1; /* board for player 1 */

static void init_screen();
static void finish(int sig);



int main(int argc, char *argv[]) {

    init_screen();
     finish(0);               
}

static void init_screen() {
    (void) signal(SIGINT, finish);      /* arrange interrupts to terminate */
    (void) initscr();      /* initialize the curses library */
    keypad(stdscr, TRUE);  /* enable keyboard mapping */
    (void) nonl();         /* tell curses not to do NL->CR/NL on output */
    (void) cbreak();       /* take input chars one at a time, no wait for \n */
    (void) noecho();       /* do not echo input */
    timeout(500);          /* wait maximum 500ms for a character */
    /* Use timeout(-1) for blocking mode */
    
    if (has_colors()) {
    
        start_color();
        // initialise you color pairs (foreground, background)
        init_pair(1, COLOR_TEXT, COLOR_BACKGROUND);
        init_pair(2, COLOR_TEXT, COLOR_2);
        init_pair(3, COLOR_TEXT, COLOR_4);
        init_pair(4, COLOR_TEXT, COLOR_8);
        init_pair(5, COLOR_TEXT, COLOR_16);
    }
    /* set default color pair */
    attrset(COLOR_PAIR(1));
}

static void finish(int sig) {
    endwin();

    /* do your non-curses wrapup here, like freeing the memory allocated */


    exit(sig);
}
