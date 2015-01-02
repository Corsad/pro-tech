#ifndef KHANH_AI
#define KHANH_AI

int getHighestScore(int **x, int row, int col);
int recursiveRun(int **x, int row, int col, int testNo);
// int recursiveRun(int **x, int row, int col, int testNo, int countEmptyOriginal);
// int surroundCheck(int **x, int row, int col);
// int pointReturn(int x, int y);
int getHighestOrSecondHighest(int **x, int row, int col, int mode);
int gradientCheck(int **x, int row, int col, int side);
double expectimax(int **x, int row, int col, int testNo);



// HIGHEST IN CORNER
int highestInCorner(int **x, int row, int col, int gradient);

// MONOTONIC
int inOrder(int **x, int row, int col, int gradient);
int checkRow(int **x, int curRow, int curCol, int mode);
int checkCol(int **x, int curRow, int curCol, int mode);

// ULTI
int assignVal(int **x, int row, int col, int newValLocation, int valMode);
void printBestMove(int **x, int row, int col);
#endif