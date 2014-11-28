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
void printMap(int **x, int row, int col);

/** Print user's score
  * @param score pointer to user sscore
  * @param row score will be printed in this row
  */
void printScore(int *score, int row);

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

/** Move the board up
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
void up(int **x, int row, int col,int *score);

/** Move the board down
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
void down(int **x, int row, int col,int *score);

/** Move the board left
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
void left(int **x, int row, int col,int *score);

/** Move the board right
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
void right(int **x, int row, int col,int *score);

/** Function pointer for up, down, left, right methods
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
void simplify(void (* func)(int **, int, int,int *), int **x, int row, int col,int *score);

/** Return goal based on the board size
  * @param row the amount of row the board has
  */
int goalCal (int row);
// void simplify(int **x, int dir, int row, int col);

/** Change color based on integer
  * @param x the integer to be changed
  */
void coloring(int x);

#endif