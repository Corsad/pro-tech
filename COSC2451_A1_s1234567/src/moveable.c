#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pt_utils.h"
#include "moveable.h"

int moveable(int **x, int row, int col){

	// Make clone array and copy it
	int **clone = malloc(sizeof(int *) * row);
	for(int i = 0; i < row; i++){
		clone[i] = malloc(sizeof(int) *col);
		copy_int_array(x[i],clone[i], col);
	}


	int (* funcs[4])(int **, int, int) = {&upTest, &downTest, &leftTest, &rightTest};

	int temp = 0;
	for(int i = 0; i < 4; i++){
		if(simplifyTest(funcs[i], x , row, col) == 1){
			temp = 1;
			break;
		}
	}

	for(int i = 0; i < row; i++){
		free(clone[i]);
	}
	free(clone);

	return temp;
}

int upTest(int **x, int row, int col){
	// x[ROW][COL] ==> x[j][i]
	for(int i = 0; i < col; i++){
		int stop = 0;
		for (int j = 1; j < row; j++)
		{			
			int k = j;
			while(k != stop){
				if(x[k - 1][i] == x[k][i] && x[k][i] != 0){
					return 1;
				}  else if (x[k - 1][i] == 0 && x[k][i] != 0 ){
					return 1;
				}
				k--;
			}
		}
	}
	return 0;
}

int downTest(int **x, int row, int col){
	// x[ROW][COL] ==> x[j][i]
	for(int i = 0; i < col ; i++){
		int stop = row - 1;
		for (int j = row - 2; j >= 0; j--)
		{
			int k = j;
			while(k != stop){
				if(x[k + 1][i] == x[k][i] && x[k][i] != 0){
					return 1;
					break;
				}  else if (x[k + 1][i] == 0 && x[k][i] != 0){
					return 1;
				}
				k++;
			}
		}
	}
	return 0;
}

int leftTest(int **x, int row, int col){
	// x[ROW][COL] ==> x[i][j]
	for(int i = 0; i < row; i++){
		int stop = 0;
		for (int j = 1; j < col; j++)
		{
			int k = j;
			while(k != stop){
				if(x[i][k-1] == x[i][k] && x[i][k] != 0){
					return 1;
				} else if (x[i][k-1] == 0 && x[i][k] != 0){
					return 1;
				}

				k--;
			}
		}
	}
	return 0;
}


int rightTest(int **x, int row, int col){
	// x[ROW][COL] ==> x[i][j]
	for(int i = 0; i < row; i++){
		int stop = col -1;
		for (int j = col -1; j >= 0; j--)
		{
			int k = j;
			while(k != stop){
				if(x[i][k+1] == x[i][k]  && x[i][k] != 0){
					return 1;
				} else if(x[i][k+1] == 0 && x[i][k] != 0){
					return 1;
				}
				k++;	
			}
		}
	}
	return 0;
}

int simplifyTest(int (* func)(int **, int, int), int **x, int row, int col) {
    return (*func)(x, row, col);
}

int goalTest(int **x,int row, int col, int *goal) {
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(x[i][j] == *goal)
				return 1;
		}
	}
	return 0;
}
