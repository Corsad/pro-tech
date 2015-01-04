#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "huyAI.h"
#include "pt_utils.h"
#include "move.h"
#include "moveable.h"
#include "random.h"
#include "math.h"

int getBestMoveHuyAI(int **x, int row, int col){
	//Function pointers
	void (* funcs[4])(int **, int, int,int *) = {&up, &down, &left, &right};
	int (* tests[4])(int **, int, int) = {&upTest,&downTest,&leftTest,&rightTest};

	//First try every move and get their scores 
	//and the number of empty spaces they create
	int *scores = malloc(sizeof(int)*4);
	int *empty = malloc(sizeof(int)*4);
	int *monotonic = malloc (sizeof(int)*4);
	
	for (int i = 0; i < 4; i++) {
		// Clone Array
			int **clone = malloc(sizeof(int *) * row);

			for(int k = 0; k < row; k++){
				clone[k] = malloc(sizeof(int) *col);
				copy_int_array(x[k],clone[k], col);
			}
        
        scores[i] = 0;
        empty[i] = countEmpty(clone,row, col);
        monotonic[i] = 0;
		if (simplifyTest(tests[i],clone,row, col)==1) {
			//Calculate scores and merges of the move
			simplify(funcs[i], clone , row, col,&scores[i]);
			//Add 1 to seperate legal and illegal moves
			//To choose a move when there are no merges
			scores[i]++;
			empty[i] = countEmpty(clone,row, col) - empty[i];	

			//Check monotonic preserverance of the move
			monotonic[i] += MonotonicTest(clone,row,col);
		} else empty[i] = 0;

		//Formular to calculate the score of each move to choose the best move
		//based on the priority of the three properties above
		//monotonic > merge > score

		scores[i] += monotonic[i]*100 + empty[i]*10;

		//Free clone array
		for(int k = 0; k < row; k++){
				free (clone[k]);
			}
		free (clone);
	}
	
	int bestMove = 0;
	for (int i = 0; i<4;i++) {
		if (scores[i]>=scores[bestMove]) 
			bestMove = i;
	}
	//Free memory
	free (scores);
	free (empty);
	free (monotonic);

	return bestMove;
}

int MonotonicTest(int **x, int row, int col){

	// x[ROW][COL] ==> x[j][i]
	for(int i = 0; i < col; i++){
		int currentRowNotEmpty = 0;
		while (x[currentRowNotEmpty][i]==0&&currentRowNotEmpty<row-1) {
			currentRowNotEmpty++;
		}

		for (int j = currentRowNotEmpty+1;j<row;j++) {
			if (x[j][i]==0)
				continue;
			else if (x[currentRowNotEmpty][i]<=x[j][i])
				currentRowNotEmpty++;
			else return 0;
		}
		
	}


	// x[ROW][COL] ==> x[j][i]
	for(int j = 0; j < row; j++){
		int currentColNotEmpty = 0;
		while (x[j][currentColNotEmpty]==0&&currentColNotEmpty<row-1) {
			currentColNotEmpty++;
		}

		for (int i = currentColNotEmpty+1;i<col;i++) {
			if (x[j][i]==0)
				continue;
			else if (x[j][currentColNotEmpty]<=x[j][i])
				currentColNotEmpty++;
			else return 0;
		}
		
	}

	return 1;
}
