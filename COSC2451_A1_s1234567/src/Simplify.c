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
int getMaxLength(int **x);
void printMap(int **x);
void up(int **x);
void down(int **x);
void left(int **x);
void right(int **x);
void simplify(int **x, int dir);
static void finish(int sig);
static void init_screen();

int main(){
	init_screen();
	int **x = malloc(sizeof(int *) * ROW);

	// There are 2 map: map.txt and map2.txt
	FILE *f = fopen("map.txt", "r");
	for(int i = 0; i < ROW; i++){
		x[i] = malloc(sizeof(int) *COL);
	}

	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL;j++){
			// printf("x[%i][%i]: ",i,j);
			// scanf("%i",&x[i][j]);
			fscanf (f, "%i", &x[i][j]);   
		}
	}
	fclose (f);     

	printMap(x);
	int c;

	// simplify(,x,,)
	// x: 1 -> Up; 2 -> Down; 3 -> Left; 4 -> Right;

	while(((c = getch()) != 'q')){
		switch(c){
			case KEY_UP:
			clear();
			simplify(x, 1);
			printMap(x);
			break;
			case KEY_DOWN:
			clear();
			simplify(x, 2);
			printMap(x);
			break;
			case KEY_LEFT:
			clear();
			simplify(x, 3);
			printMap(x);
			break;
			case KEY_RIGHT:
			clear();
			simplify(x, 4);
			printMap(x);
			break;
		}
	}

	finish(0);
	return 0;
}

int getIntLength(int x){
	if(x == 0){
		return 1;
	} else {
		return (int)log10(x)+1;
	}
}

int getMaxLength(int **x){
	int temp = 0;
	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL; j++){
			if(temp < x[i][j])
				temp = x[i][j];
		}
	}
	return temp;
}

void printMap(int **x){
	int cellLength = getMaxLength(x) + 1;
	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL; j++){
			mvprintw((CELLHEIGHT + i * CELLHEIGHT), (cellLength + (cellLength*j) - getIntLength(x[i][j])), "%i", x[i][j]);
		}
	}
}

void up(int **x){
	// x[ROW][COL] ==> x[j][i]
	for(int i = 0; i < COL; i++){
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

void down(int **x){
	// x[ROW][COL] ==> x[j][i]
	for(int i = 0; i < COL ; i++){
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

void left(int **x){
	// x[ROW][COL] ==> x[i][j]
	for(int i = 0; i < ROW; i++){
		int stop = 0;
		for (int j = 1; j < COL; j++)
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


void right(int **x){
	// x[ROW][COL] ==> x[i][j]
	for(int i = 0; i < ROW; i++){
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

void simplify(int **x, int dir)
{
	printf("test\n");
	switch(dir){
		case 1:
			printf("up method\n");
			up(x);
			printf("up\n");
			break;
		case 2:
			printf("down method\n");
			down(x);
			printf("down\n");
			break;
		case 3:
			left(x);
			printf("left\n");
			break;
		case 4:
			right(x);
			printf("right\n");
			break;
	}
}

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