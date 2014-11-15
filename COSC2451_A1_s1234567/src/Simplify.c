#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include <math.h>

#define ROW 4
#define COL 4
#define CELLHEIGHT 4

int getIntLength(int x);
int getMaxLength(int **x, int row, int col);
void printMap(int **x, int row, int col);
void up(int **x, int row, int col);
void down(int **x, int row, int col);
void left(int **x, int row, int col);
void right(int **x, int row, int col);
void simplify(void (* func)(int **, int, int), int **x, int row, int col);
// void simplify(int **x, int dir, int row, int col);
static void finish(int sig);
static void init_screen();

int main(){
	init_screen();
	int **x = malloc(sizeof(int *) * ROW);

	for(int i = 0; i < ROW; i++){
		x[i] = malloc(sizeof(int) *COL);
	}

	// There are 2 map: map.txt and map2.txt
	FILE *f = fopen("map.txt", "r");
	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL;j++){
			// printf("x[%i][%i]: ",i,j);
			// scanf("%i",&x[i][j]);
			fscanf (f, "%i", &x[i][j]);   
		}
	}
	fclose (f);     

	printMap(x, ROW, COL);
	int c;

	// simplify(,x,,)
	// x: 1 -> Up; 2 -> Down; 3 -> Left; 4 -> Right;

	void (* funcs[4])(int **, int, int) = {&up, &down, &left, &right};
	while(((c = getch()) != 'q')){
		switch(c){
			case KEY_UP:
			clear();
			simplify(funcs[0], x , ROW, COL);
			printMap(x, ROW, COL);
			break;
			case KEY_DOWN:
			clear();
			simplify(funcs[1], x , ROW, COL);
			printMap(x, ROW, COL);
			break;
			case KEY_LEFT:
			clear();
			simplify(funcs[2], x , ROW, COL);
			printMap(x, ROW, COL);
			break;
			case KEY_RIGHT:
			clear();
			simplify(funcs[3], x , ROW, COL);
			printMap(x, ROW, COL);
			break;
		}
	}

	for(int i = 0; i < ROW; i++){
		free(x[i]);
	}
	free(x);
	finish(0);
	return 0;
}

int countEmpty(int **x, int row, int col){
	int temp = 0;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(x[i][j] == 0)
				temp++;
		}
	}
	return temp;
}

// int moveable(int **x, int row, int col){

// 	// Make clone array and copy it
// 	int **clone = malloc(sizeof(int *) * row);
// 	for(int i = 0; i < row; i++){
// 		clone[i] = malloc(sizeof(int) *col);
// 		copy_int_array(x[i],clone[i], col);
// 	}

// 	for(int i = 0; i < 4; i++){

// 	}

// 	for(int i = 0; i < row; i++){
// 		free(clone[i]);
// 	}
// 	free(clone);
// }

int getIntLength(int x){
	if(x == 0){
		return 1;
	} else {
		return (int)log10(x)+1;
	}
}

int getMaxLength(int **x, int row, int col){
	int temp = 0;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(temp < getIntLength(x[i][j]))
				temp = getIntLength(x[i][j]);
		}
	}
	return temp;
}

void printMap(int **x, int row, int col){
	int cellLength = getMaxLength(x, row, col) + 1;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			// mvprintw((CELLHEIGHT + i * CELLHEIGHT), (cellLength + (cellLength*j) - getIntLength(x[i][j])), "%i", x[i][j]);
			mvprintw((CELLHEIGHT + i * CELLHEIGHT), (5 + (5*j) - getIntLength(x[i][j])), "%i", x[i][j]);
		}
	}
}

void up(int **x, int row, int col){
	// x[ROW][COL] ==> x[j][i]
	for(int i = 0; i < col; i++){
		int stop = 0;
		for (int j = 1; j < ROW; j++)
		{			
			int k = j;
			while(k != stop){
				if(x[k - 1][i] == x[k][i] && x[k][i] != 0){
					x[k - 1][i] += x[k][i];
					x[k][i] = 0;
					stop = k;
					break;
				}  else if (x[k - 1][i] == 0){
					x[k - 1][i] += x[k][i];
					x[k][i] = 0;
				}
				k--;
			}
		}
	}
}

void down(int **x, int row, int col){
	// x[ROW][COL] ==> x[j][i]
	for(int i = 0; i < col ; i++){
		int stop = ROW - 1;
		for (int j = ROW - 2; j >= 0; j--)
		{
			int k = j;
			while(k != stop){
				if(x[k + 1][i] == x[k][i] && x[k][i] != 0){
					x[k + 1][i] += x[k][i];
			 		x[k][i] = 0;
					stop = k;
					break;
				}  else if (x[k + 1][i] == 0){
					x[k + 1][i] += x[k][i];
					x[k][i] = 0;
				}
				k++;
			}
		}
	}
}

void left(int **x, int row, int col){
	// x[ROW][COL] ==> x[i][j]
	for(int i = 0; i < row; i++){
		int stop = 0;
		for (int j = 1; j < col; j++)
		{
			int k = j;
			while(k != stop){
				if(x[i][k-1] == x[i][k] && x[i][k] != 0){
					x[i][k-1] += x[i][k];
					x[i][k] = 0;
					stop = k;
					break;
				} else if (x[i][k-1] == 0){
					x[i][k-1] += x[i][k];
					x[i][k] = 0;
				}

				k--;
			}
		}
	}
}


void right(int **x, int row, int col){
	// x[ROW][COL] ==> x[i][j]
	for(int i = 0; i < row; i++){
		int stop = COL -1;
		for (int j = COL -1; j >= 0; j--)
		{
			int k = j;
			while(k != stop){
				if(x[i][k+1] == x[i][k]  && x[i][k] != 0){
					x[i][k+1] += x[i][k];
					x[i][k] = 0;
					stop = k;
					break;
				} else if(x[i][k+1] == 0){
					x[i][k+1] += x[i][k];
					x[i][k] = 0;
				}
				k++;	
			}
		}
	}
}

void simplify(void (* func)(int **, int, int), int **x, int row, int col) {
    (*func)(x, row, col);
}

// void simplify(int **x, int dir, int row, int col)
// {
// 	switch(dir){
// 		case 1:
// 			up(x, row, col);
// 			break;
// 		case 2:
// 			down(x, row, col);
// 			break;
// 		case 3:
// 			left(x, row, col);
// 			break;
// 		case 4:
// 			right(x, row, col);
// 			break;
// 	}
// }

static void finish(int sig) {
    endwin();

    /* do your non-curses wrapup here, like freeing the memory allocated */


    exit(sig);
}

static void init_screen() {
	(void) signal(SIGINT, finish);
	(void) initscr(); 
	(void) nonl();         
    (void) cbreak(); 
    (void) noecho();      
    keypad(stdscr, TRUE);   
    timeout(-1);
}