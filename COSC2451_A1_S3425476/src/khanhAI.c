#include <stdio.h>
#include <stdlib.h>

#include "khanhAI.h"
#include "pt_utils.h"
#include "move.h"
#include "random.h"

int getBestMove(int **x, int row, int col){
	int BestMove;
	
	getHighestScore(x, row, col);
	return BestMove;
}

int getHighestScore(int **x, int row, int col){
		int temp = 0;
		int move = 0;
		int score = 0;
		int testNo = 0;

		void (* funcs[4])(int **, int, int,int *) = {&up, &down, &left, &right};

		for(int i = 0; i < 4; i++){

			// Clone Array
			int **clone = malloc(sizeof(int *) * row);

			for(int k = 0; k < row; k++){
				clone[k] = malloc(sizeof(int) *col);
				copy_int_array(x[k],clone[k], col);
			}

			///////
			simplify(funcs[i], clone , row, col, &score);
			testNo = 0;

			recursiveRun(clone, row, col, &score, &testNo);

			if(temp < score){
				temp = score;
				move = i;
			}

			score = 0;
			// Free Array	
			for(int k = 0; k < row; k++){
				free(clone[k]);
			}
			free(clone);
			///////
		}

		return move;
}

void recursiveRun(int **x, int row, int col, int *score, int *testNo){
	if(*testNo != 2){
		int temp = *score;
		int empty = countEmpty(x, row, col);

		void (* funcs[4])(int **, int, int,int *) = {&up, &down, &left, &right};

		for(int i = 0; i < empty; i++){	
			for(int j = i + 1; j < empty; j++){

				// Clone Array
				int **clone = malloc(sizeof(int *) * row);

				for(int k = 0; k < row; k++){
					clone[k] = malloc(sizeof(int) *col);
					copy_int_array(x[k],clone[k], col);
				}
				///////		

				assignVal(clone, row, col, i);
				assignVal(clone, row, col, j);

				simplify(funcs[i], clone , row, col, score);

				testNo++;
				recursiveRun(clone, row, col, score, testNo);

				if(temp < *score){
					temp = *score;
				}

				// Free Array			
				for(int k = 0; k < row; k++){
					free(clone[k]);
				}
				free(clone);
				///////	
			}
		}

	}
}

int assignVal(int **x, int row, int col, int newValLocation){
	int temp = 0;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(x[i][j] == 0)
				temp++;
			if (temp == newValLocation) {
				x[i][j] = 2;
				return 1;
			}
		}
	}

	return 0;
}