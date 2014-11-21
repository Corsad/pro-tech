#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include <math.h>


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

int randomVal(int **x, int row, int col) {
	int empty = countEmpty(x,row,col);
	
	int randomVal = rand()%10==0?4:2;
	int randomPlace = rand()%empty+1;

	int temp = 0;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(x[i][j] == 0)
				temp++;
			if (temp==randomPlace) {
				x[i][j] = randomVal;
				break;
			}
		}
	}
	return 0;
}