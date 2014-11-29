#ifndef HEADER_FILE
#define HEADER_FILE

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

#endif