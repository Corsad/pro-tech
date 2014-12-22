#ifndef KHANH_AI
#define KHANH_AI

int getHighestScore(int **x, int row, int col);
void recursiveRun(int **x, int row, int col, int *score, int testNo, int countEmptyOriginal);
int assignVal(int **x, int row, int col, int newValLocation);
void printBestMove(int **x, int row, int col);
int highestInCorner(int **x, int row, int col);
#endif