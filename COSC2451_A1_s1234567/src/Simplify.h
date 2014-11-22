#ifndef HEADER_FILE
#define HEADER_FILE

int playGame();
int getIntLength(int x);
int getMaxLength(int **x, int row, int col);
void printMap(int **x, int row, int col);
void printScore(int *score, int row);
void up(int **x, int row, int col,int *score);
void down(int **x, int row, int col,int *score);
void left(int **x, int row, int col,int *score);
void right(int **x, int row, int col,int *score);
void simplify(void (* func)(int **, int, int,int *), int **x, int row, int col,int *score);
// void simplify(int **x, int dir, int row, int col);
static void finish(int sig);
static void init_screen();

#endif