#ifndef DRAWMENU
#define DRAWMENU

static void init_screen();
static void doChoice(int * currentChoice);
static void drawMenu(int * currentChoice);
static void doBoardChoice(int boardChoice);
static void drawBoardMenu();
static void finish(int sig);
static void printCredit();
void defaultColor();
void definePair();
#endif