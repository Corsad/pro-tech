#ifndef RANDOM
#define RANDOM

/** return the amount of empty space on the board
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
int countEmpty(int **x, int row, int col);

/** Assign 2 or 4 to the empty space
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
int randomVal(int **x, int row, int col);

#endif