#ifndef HEADER_FILE
#define HEADER_FILE

/** Play game 1 person
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
  * @param playerAmount 2 players/AI or 1 player/AI
  */
void printMap(int **x, int row, int col, int playerAmount);

/** Print user's score
  * @param score pointer to user sscore
  * @param row score will be printed in this row
  * @param playerAmount 2 players/AI or 1 player/AI
  */
void printScore(int *score, int row, int playerAmount);

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

/** Play game 1 AI
  * @param ROW the amount of row the board will have
  * @param COL the amount of column the board will have
  * @param AIFuncs get move from AI's function
  */
int playGameAI(int ROW,int COL, int (* AIFuncs)(int **, int, int));

/** Play game 2 players without limit time
  * @param ROW the amount of row the board will have
  * @param COL the amount of column the board will have
  */
int playGame2Player(int ROW,int COL);

/** Play game 1 AI vs 1 Player
  * @param ROW the amount of row the board will have
  * @param COL the amount of column the board will have
  * @param AIFuncs get move from AI's function
  */
int playGamePlayerVsAI(int ROW,int COL, int (* AIFuncs)(int **, int, int));

/** Play game 2 AI
  * @param ROW the amount of row the board will have
  * @param COL the amount of column the board will have
  * @param AIFuncs get move from AI's function
  * @param AIFuncs2 get move from AI's function
  */
int playGameAIVsAI(int ROW,int COL, int (* AIFuncs)(int **, int, int),int (* AIFuncs2)(int **, int, int));

/** Play game 2 Players with limit time
  * @param ROW the amount of row the board will have
  * @param COL the amount of column the board will have
  * @param minutes time play in minute
  * @param seconds time play in second
  */
int playGame2PlayerLimited(int ROW,int COL, int minutes, int seconds);

#endif