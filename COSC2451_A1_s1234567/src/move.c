#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "pt_utils.h"
#include "move.h"

void up(int **x, int row, int col, int *score){
	// x[ROW][COL] ==> x[j][i]
	for(int i = 0; i < col; i++){
		int stop = 0;
		for (int j = 1; j < row; j++)
		{			
			int k = j;
			while(k != stop){
				if(x[k - 1][i] == x[k][i] && x[k][i] != 0){
					x[k - 1][i] += x[k][i];
					*score += x[k - 1][i];
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

void down(int **x, int row, int col, int *score){
	// x[ROW][COL] ==> x[j][i]
	for(int i = 0; i < col ; i++){
		int stop = row - 1;
		for (int j = row - 2; j >= 0; j--)
		{
			int k = j;
			while(k != stop){
				if(x[k + 1][i] == x[k][i] && x[k][i] != 0){
					x[k + 1][i] += x[k][i];
					*score += x[k + 1][i];
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

void left(int **x, int row, int col, int *score){
	// x[ROW][COL] ==> x[i][j]
	for(int i = 0; i < row; i++){
		int stop = 0;
		for (int j = 1; j < col; j++)
		{
			int k = j;
			while(k != stop){
				if(x[i][k-1] == x[i][k] && x[i][k] != 0){
					x[i][k-1] += x[i][k];
					*score += x[i][k-1];
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


void right(int **x, int row, int col, int *score){
	// x[ROW][COL] ==> x[i][j]
	for(int i = 0; i < row; i++){
		int stop = col -1;
		for (int j = col -1; j >= 0; j--)
		{
			int k = j;
			while(k != stop){
				if(x[i][k+1] == x[i][k]  && x[i][k] != 0){
					x[i][k+1] += x[i][k];
					*score += x[i][k+1];
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

void simplify(void (* func)(int **, int, int, int *), int **x, int row, int col, int *score) {
    (*func)(x, row, col,score);
}