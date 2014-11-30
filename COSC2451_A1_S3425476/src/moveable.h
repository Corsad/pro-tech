#ifndef MOVEABLE
#define MOVEABLE

/** Check if the game can still be continued
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
int moveable(int **x, int row, int col);

/** Check if user can press Up
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
int upTest(int **x, int row, int col);

/** Check if user can press Down
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
int downTest(int **x, int row, int col);

/** Check if user can press Left
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
int leftTest(int **x, int row, int col);

/** Check if user can press Right
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
int rightTest(int **x, int row, int col);

/** Function pointer for upTest, downTest, leftTest, rightTest
  * @param func function pointer to function needed
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
int simplifyTest(int (* func)(int **, int, int), int **x, int row, int col);

/** Check the user has reached the goal
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  * @param goal the score user need to check
  */
int goalTest(int **x,int row, int col, int *goal);


/** Return goal based on the board size
  * @param row the amount of row the board has
  */
int goalCal (int row);

#endif