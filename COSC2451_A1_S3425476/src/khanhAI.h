#ifndef KHANH_AI
#define KHANH_AI

int getBestMove(int **x, int row, int col);
int getHighestScore(int **x, int row, int col);
void recursiveRun(int **x, int row, int col, int *score, int *testNo);
int assignVal(int **x, int row, int col, int newValLocation);

#endif