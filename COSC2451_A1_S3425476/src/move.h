#ifndef MOVE
#define MOVE

/** Move the board up
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  * @param score user current score
  */
void up(int **x, int row, int col,int *score);

/** Move the board down
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  * @param score user current score
  */
void down(int **x, int row, int col,int *score);

/** Move the board left
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  * @param score user current score
  */
void left(int **x, int row, int col,int *score);

/** Move the board right
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  * @param score user current score
  */
void right(int **x, int row, int col,int *score);

/** Function pointer for up, down, left, right methods
  * @param func pointer to function needed
  * @param x the double array represent the board
  * @param row the amount of row the board has
  * @param col the amount of column the board has 
  * @param score user current score
  */
void simplify(void (* func)(int **, int, int,int *), int **x, int row, int col,int *score);

#endif