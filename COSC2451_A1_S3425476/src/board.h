#ifndef HEADER_FILE
#define HEADER_FILE

/** Take input from user
  * @param ROW the amount of row the board will have
  * @param COL the amount of column the board will have
  */
int playGame(int ROW, int COL);

/** Return the amount of char of an integer
  * @param x the integer that need to be check
  */
int getIntLength(int x);

/** Return the amount of char of an integer
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
int getMaxLength(int **x, int row, int col);

/** Print the board using ncurses
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
void printMap(int **x, int row, int col, int location);

/** Print user's score
  * @param score pointer to user sscore
  * @param row score will be printed in this row
  */
void printScore(int *score, int row, int location);

/** Announce game over
  * @param row the announcement will be printed in this row
  */
void printOver(int row);

/** Print current goal
  * @param row the goal will be printed in this row
  * @param goal pointer to current goal
  */
void printGoal(int row, int *goal);

/** Print user has reached the goal
  * @param row the announcement will be printed in this row
  * @param goal pointer to current goal
  */
void printGoalReached(int row, int *goal); 

/** Change color based on integer
  * @param x the integer to be changed
  */
void coloring(int x);

int playGameAI(int ROW,int COL, int (* AIFuncs)(int **, int, int));
int playGame2Player(int ROW,int COL);
int playGamePlayerVsAI(int ROW,int COL, int (* AIFuncs)(int **, int, int));
int playGameAIVsAI(int ROW,int COL, int (* AIFuncs)(int **, int, int),int (* AIFuncs2)(int **, int, int));
#endif