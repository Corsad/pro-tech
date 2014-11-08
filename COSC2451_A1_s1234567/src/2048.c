#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <assert.h>

#define DEFAULT_BOARD_SIZE 4
#define DEAFULT_GOAL 2048

int board_size = DEFAULT_BOARD_SIZE;

unsigned int **board_p1; /* board for player 1 */

static void init_boards();
static void init_screen();
static void finish(int sig);


int main(int argc, char *argv[]) {

    int x = 0, y = 0, maxx, maxy;
    char c;

    struct timespec delay = {0, 500000000L}, 
                     rem;

    init_boards();
    init_screen();
    
    for (;;) {
        int c = getch();     /* refresh, accept single keystroke of input */
        
        /* process the command keystroke */
        if (c == 'q') {
            break;
        }

        getmaxyx(stdscr, maxy, maxx);
        if (c == KEY_DOWN && y < maxy-1) {
            y++;
        } else if (c == KEY_RIGHT && x < maxx-1) {
            x++;
        } else if (c == KEY_UP && y > 0) {
            y--;
        } else if (c == KEY_LEFT && x > 0) {
            x--;
        } else if (c == 'a') {
            addch('2');
        }
        else if (c == ' ' || c == -1) {
            c = mvinch(y, x);
            addch('!');
        }
        move(y, x);
	    
	    // sleep 
        //nanosleep(&delay, &rem);
    }

    finish(0);               /* we're done */
}

static void init_boards() {
    board_p1 = NULL;
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
}

static void finish(int sig) {
    endwin();

    /* do your non-curses wrapup here, like freeing the memory allocated */


    exit(sig);
}
