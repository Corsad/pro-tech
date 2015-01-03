#ifndef KHANH_AI
#define KHANH_AI

/** Calculate best move for AI
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
int getBestMoveKhanhAI(int **x, int row, int col);


// int recursiveRun(int **x, int row, int col, int testNo);
// int recursiveRun(int **x, int row, int col, int testNo, int countEmptyOriginal);
// int surroundCheck(int **x, int row, int col);
// int pointReturn(int x, int y);


// GRADIENT
/** Return best gradient for map
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  * @param side the side that need to be checked
  */
int gradientCheck(int **x, int row, int col, int side);


// EXPECTIMAX
/** Calculate score based on expectimax
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  * @param testNo the amount of move the board will play ahead
  */
double expectimax(int **x, int row, int col, int testNo);


// HIGHEST IN CORNER
/** Check if highest on board is in corner
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  * @param gradient check if highest is in that gradient's corner
  */
int highestInCorner(int **x, int row, int col, int gradient);

// MONOTONIC
/** Check if the board is going from highest to lowest based on gradient
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  * @param gradient check monotonic based on gradient
  */
int inOrder(int **x, int row, int col, int gradient);

/** Check order for row
  * @param x the double array represent the board
  * @param curRow the row that need to be checked
  * @param curCol the starting point for col
  * @param mode check top to bottom or left to right
  */
int checkRow(int **x, int curRow, int curCol, int mode);

/** Check order for col
  * @param x the double array represent the board
  * @param curRow the starting point for row
  * @param curCol the col that need to be checked
  * @param mode check top to bottom or left to right
  */
int checkCol(int **x, int curRow, int curCol, int mode);

// ULTI
/** Assigning new value for array
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  * @param newValLocation location for new Value based on empty
  * @param valMode Value is 2 or 4
  */
int assignVal(int **x, int row, int col, int newValLocation, int valMode);

/** Print out best move for checking purpose
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  */
void printBestMove(int **x, int row, int col);

/** Return the amount of char of an integer
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  * @param mode get highest or get second highest
  */
int getHighestOrSecondHighest(int **x, int row, int col, int mode);

#endif