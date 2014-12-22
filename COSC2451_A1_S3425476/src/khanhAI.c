#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "khanhAI.h"
#include "pt_utils.h"
#include "move.h"
#include "moveable.h"
#include "random.h"

void printBestMove(int **x, int row, int col){
	int bestMove = getHighestScore(x, row, col);
	switch(bestMove){
		case 0:
			mvprintw(20,20, "^");
			break;
		case 1:
			mvprintw(20,20, "v");
			break;
		case 2:
			mvprintw(20,20, "<");
			break;
		case 3:
			mvprintw(20,20, ">");
			break;		
	}
}

int getHighestScore(int **x, int row, int col){
		int temp = 0;
		int move = 0;
		int *score = malloc(sizeof(int) * 4);	
		int countEmptyOriginal = countEmpty(x, row, col);

		void (* funcs[4])(int **, int, int,int *) = {&up, &down, &left, &right};
		int (* funcsTest[4])(int **, int, int) = {&upTest, &downTest, &leftTest, &rightTest};

		for(int i = 0; i < 4; i++){
			if(simplifyTest(funcsTest[i], x , row, col) == 1){
				score[i] = 0;
				// Clone Array
				int **clone = malloc(sizeof(int *) * row);

				for(int k = 0; k < row; k++){
					clone[k] = malloc(sizeof(int) *col);
					copy_int_array(x[k],clone[k], col);
				}

				///////
				simplify(funcs[i], clone , row, col, &score[i]);

				recursiveRun(clone, row, col, &score[i], 0, countEmptyOriginal);

				if(highestInCorner(clone, row, col) == 1){
					score[i] += 10000;
				}
				
				if(temp < score[i]){
					temp = score[i];
					move = i;
					mvprintw(20+i+1,20, "%i", temp);
				}

				// Free Array	
				for(int k = 0; k < row; k++){
					free(clone[k]);
				}
				free(clone);
				///////
			}
		} 

		if(simplifyTest(funcsTest[move], x , row, col) != 1){
			for(int i = 0; i < 4; i++){
				if(simplifyTest(funcsTest[i], x , row, col) == 1){
					move = i;
				}
			}
		}

		return move;
}

void recursiveRun(int **x, int row, int col, int *score, int testNo, int countEmptyOriginal){
	if(testNo != 1){
		int temp = *score;
		int empty = countEmpty(x, row, col);
		void (* funcs[4])(int **, int, int,int *) = {&up, &down, &left, &right};
		int (* funcsTest[4])(int **, int, int) = {&upTest, &downTest, &leftTest, &rightTest};

		for(int i = 0; i < empty; i++){	
			for(int j = i + 1; j < empty; j++){
				for(int k = 0; k < 4; k++){
					if(simplifyTest(funcsTest[k], x , row, col) == 1){
						// Clone Array
						int **clone = malloc(sizeof(int *) * row);

						for(int k = 0; k < row; k++){
							clone[k] = malloc(sizeof(int) *col);
							copy_int_array(x[k],clone[k], col);
						}
						///////		

						assignVal(clone, row, col, i);
						assignVal(clone, row, col, j);

						simplify(funcs[k], clone , row, col, score);								
						recursiveRun(clone, row, col, score, testNo + 1, countEmptyOriginal);
						
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
	} else {
		int empty = countEmpty(x, row, col);
		if(countEmptyOriginal < empty){
			*score += (empty - countEmptyOriginal) * 200;
		}
	}
}

int highestInCorner(int **x, int row, int col){
	int temp = 0;
	int highestX;
	int highestY;
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j++){
			if (temp < x[i][j]){
				temp = x[i][j];
				highestX = i;
				highestY = j;
			} 
		}
	}



	if((highestX == 0 || highestX == 3) && (highestY == 0 || highestY == 3)){
		return 1;
	}
	return 0;
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