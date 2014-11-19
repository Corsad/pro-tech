#ifndef MOVEABLE
#define MOVEABLE

int moveable(int **x, int row, int col);
int upTest(int **x, int row, int col);
int downTest(int **x, int row, int col);
int leftTest(int **x, int row, int col);
int rightTest(int **x, int row, int col);
int simplifyTest(int (* func)(int **, int, int), int **x, int row, int col);

#endif