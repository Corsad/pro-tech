#ifndef HUY_AI
#define HUY_AI


/** Calculate best move for Huy AI
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
int getBestMoveHuyAI(int **x, int row, int col);

/** Test if the board is sorted (ignoring free spaces) in increasing order
  * from left to right and up to down (to force the largest tile into lower right corner) 
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
int MonotonicTest(int **x, int row, int col);

#endif