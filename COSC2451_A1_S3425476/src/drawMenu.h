#ifndef DRAWMENU
#define DRAWMENU

/** Initialize ncurses 
  */
static void init_screen();

/** Call method based on user choice from menu
  * @param currentChoice pointer to menu current selected item
  */
static void doChoice(int * currentChoice);

/** Draw the main menu using ncurses
  * @param currentChoice menu current selected item
  */
static void drawMenu(int * currentChoice);

/** Select the size for board
  * @param modeChoice play or show high score
  * @param boardChoice size of the board
  */
static void doBoardChoice(int modeChoice, int boardChoice);

/** Draw the board size menu using ncurses
  * @param modeChoice play or show high score
  */
static void drawBoardMenu(int modeChoice);

/** Turn off ncurses
  * @param sig signal to end game
  */
static void finish(int sig);

/** Print info about the owner of the game
  */
static void printCredit();

/** Reset ncurses color to normal
  */
void defaultColor();

/** Initialize color pair
  */
void definePair();

/** Check if user really want to quit the game
  * @param currentChoice menu current selected item
  * @param c user previous input
  */
void printQuit(int * currentChoice, char c);

void PlayerSelectionMenu();

void selectAI(int amountOfPlayer);
#endif