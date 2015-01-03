#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "khanhAI.h"
#include "pt_utils.h"
#include "move.h"
#include "moveable.h"
#include "random.h"
#include "math.h"

#define MAX_RECURSIVE 2

void (* funcs[4])(int **, int, int,int *) = {&up, &down, &left, &right};
int (* funcsTest[4])(int **, int, int) = {&upTest, &downTest, &leftTest, &rightTest};
int bestGradient = 0;

void printBestMove(int **x, int row, int col){
	int bestMove = getBestMoveKhanhAI(x, row, col);
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

int getBestMoveKhanhAI(int **x, int row, int col){
		double temp = 0;
		int move = 0;
		double *score = malloc(sizeof(double) * 4);	
		int countEmptyOriginal = countEmpty(x, row, col);

		// int curGradient;
		// int curGradientTotal = 0;
		// for(int i = 0; i < 4; i++){
		// 	curGradientTotal = gradientCheck(x, row, col,i);
		// 	if(temp < curGradientTotal)
		// 		curGradient = i;
		// }
		
		temp = 0;
		for(int i = 0; i < 4; i++){
			if(simplifyTest(funcsTest[i], x , row, col) == 1){
				score[i] = 0;
				// Clone Array
				int **clone = malloc(sizeof(int *) * row);

				for(int k = 0; k < row; k++){
					clone[k] = malloc(sizeof(int) *col);
					copy_int_array(x[k],clone[k], col);
				}

				// MIN MAX
				///////
				// simplify(funcs[i], clone , row, col, &score[i]);
				// score[i] *= 2;
				// // recursiveRun(clone, row, col, &score[i], 0, countEmptyOriginal);

				// if(highestInCorner(clone, row, col) == 1){
				// 	score[i] += 100;
				// }
				
				// int empty = countEmpty(clone, row, col);
				// if(countEmptyOriginal < empty){
				// 	score[i] += (empty - countEmptyOriginal) * 4;
				// }

				// score[i] += surroundCheck(clone, row, col);
				///////


				//MIN MAX WITH Gradient
				///////
				// simplify(funcs[i], clone , row, col, &score[i]);

				// // int empty = countEmpty(clone, row, col);
				// // if(countEmptyOriginal < empty){
				// // 	score[i] += (empty - countEmptyOriginal);
				// // }

				// // score[i] += inOrder(clone, row, col);

				// int tempGradient = 0;
				// int tempGradientTotal = 0;
				// for(int k = 0; k < 4; k++){
				// 	int tempGradientTotal = gradientCheck(clone, row, col, k);
				// 	if(curGradientTotal < tempGradientTotal){
				// 		curGradientTotal = tempGradientTotal;
				// 		tempGradient = k;
				// 	}
				// }

				// if(tempGradient == curGradient){
				// 	move = i;
				// }
				///////


				// EXPECTIMAX + HIGHEST IN CORNER + GRADIENT + MONOTONIC
				int tempScore;
				simplify(funcs[i], clone , row, col, &tempScore);
				score[i] = expectimax(clone, row, col, MAX_RECURSIVE);
				mvprintw(21 + i,20,"Score:%f", score[i]);
				//////
				// Free Array	
				for(int k = 0; k < row; k++){
					free(clone[k]);
				}
				free(clone);
				///////
			}
		}

		for(int i = 0; i < 4; i++){
			if(score[i] > temp){
				move = i;
				temp = score[i];
			}
		}

		if(simplifyTest(funcsTest[move], x , row, col) != 1){
			for(int i = 0; i < 4; i++){
				if(simplifyTest(funcsTest[i], x , row, col) == 1){
					move = i;
				}
			}
		}

		free(score);
		return move;
}

double expectimax(int **x, int row, int col, int testNo){
	if(testNo != MAX_RECURSIVE){
		double total = 0;
		double score = 0;
		double probability = 0;
		double temp = 0;
		// Find empty space

		int empty = countEmpty(x, row, col);
		for(int i = 0; i < empty; i++){	

 			// Assign 2 and 4 for all position
 			for(int j = 0; j < 2; j++){

 				// Move direction for simplify

 				for(int k = 0; k < 4; k++){
	 				// Clone
	 				int **clone = malloc(sizeof(int *) * row);

					for(int m = 0; m < row; m++){
						clone[m] = malloc(sizeof(int) *col);
						copy_int_array(x[m],clone[m], col);
					}

					// assign 2 and 4
					assignVal(clone, row, col, i, j);

					int tempScore;
					simplify(funcs[k], clone , row, col, &tempScore);							
					temp = expectimax(clone, row, col, testNo + 1);

					if (temp > score){
						score = temp;
					}			
				
					// Free Array
					for(int m = 0; m < row; m++){
 							free(clone[m]);
					}
					free(clone);
				}

				if(j == 0){
					total += (0.9*score) ;
					probability += 0.9;
				} else {
					total += (0.1*score);
					probability += 0.1;
				}
 			}
		}

		if(probability != 0){
			return total/probability;
		} else {
			return 0;
		}
	} else {

		// Check best total point this direction could have
		int total;
		int bestGradient;
		for(int i = 0; i < 4; i++){
			double temp = gradientCheck(x, row, col, i);
			temp += highestInCorner(x, row, col, i)*20;
			temp += inOrder(x,row, col, i) * 10;
			if(total < temp){
				total = temp;
				bestGradient = i;
			}
		}

		return total;
	}
}



// int recursiveRun(int **x, int row, int col, int testNo, int countEmptyOriginal){
// 	if(testNo != 1){
// 		int temp = 0;
// 		int *score = malloc(sizeof(int) * 4);
// 		int empty = countEmpty(x, row, col);
// 		void (* funcs[4])(int **, int, int,int *) = {&up, &down, &left, &right};
// 		int (* funcsTest[4])(int **, int, int) = {&upTest, &downTest, &leftTest, &rightTest};

// 		for(int i = 0; i < empty; i++){	
// 			for(int j = i + 1; j < empty; j++){
// 				for(int k = 0; k < 4; k++){
// 					if(simplifyTest(funcsTest[k], x , row, col) == 1){
// 						// Clone Array
// 						int **clone = malloc(sizeof(int *) * row);

// 						for(int m = 0; m < row; m++){
// 							clone[m] = malloc(sizeof(int) *col);
// 							copy_int_array(x[m],clone[m], col);
// 						}
// 						///////		

// 						assignVal(clone, row, col, i);
// 						assignVal(clone, row, col, j);

// 						simplify(funcs[k], clone , row, col, &score[k]);								
// 						score[k] += recursiveRun(clone, row, col, testNo + 1, countEmptyOriginal);
						
// 						if(temp < score[k]){
// 							temp = score[k];
// 						}

// 						// Free Array			
// 						for(int m = 0; m < row; m++){
// 							free(clone[m]);
// 						}
// 						free(clone);
// 						///////	
// 					}
// 				}
// 			}
// 		}

// 		free(score);
// 		return temp;
// 	}

// 	return 0;
// }

int gradientCheck(int **x, int row, int col, int side){
	int **clone = malloc(sizeof(int *) * row);

	for(int i = 0; i < row; i++){
		clone[i] = malloc(sizeof(int) *col);
	}

	switch(side){
		// Top-Left
		case 0:
			for(int i = 0; i < row; i++){
				for (int j = 0; j < col; j++){
					clone[i][j] = 3 - i - j;
				}
			}
			break;

		// Top-Right
		case 1:
			for(int i = 0; i < row; i++){
				for (int j = 0; j < col; j++){
					clone[i][j] = 0 - i +j;
				}
			}

			break;

		// Bottom-Left
		case 2:
			for(int i = 0; i < row; i++){
				for (int j = 0; j < col; j++){
					clone[i][j] = i -j;
				}
			}
			break;

		// Bottom-Right
		case 3:
			for(int i = 0; i < row; i++){
				for (int j = 0; j < col; j++){
					clone[i][j] =  j -3 + i;
				}
			}
			break;
	}

	int total = 0;
	for(int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			total += clone[i][j] * log2(x[i][j]);
		}
	}

	return total;
}


// MONOTONIC
int inOrder(int **x, int row, int col, int gradient){
	int total = 0;

	switch(gradient){
		case 0:
		case 1:
			for(int i = 0; i < row; i ++){
				total += checkRow(x, i, 0, 1);
			}			
			break;
		case 2:
		case 3:
			for(int i = 0; i < row; i ++){
				total += checkRow(x, i, 0, 0);
			}
			break;
	}

	switch(gradient){
		case 0:
		case 1:
			for(int i = 0; i < col; i ++){
				total += checkCol(x, 0, i, 1);
			}
			break;
		case 2:
		case 3:
			for(int i = 0; i < col; i ++){
				total += checkCol(x, 0, i, 0);
			}
	}

	return total;
}

int checkRow(int **x, int curRow, int curCol, int mode){
	switch(curCol){
		case 3:
			return 1;
			break;
		default:
			// 0 Higher from top to bottom
			// 1 Higher from bottom to top
			switch(mode){

				case 0:
					if(x[curRow][curCol] >= x[curRow][curCol + 1]){
						if(checkRow(x, curRow, curCol + 1, mode) != 1){
							return -1;
						}
						return 1;
					} 
					break;

				case 1:
					if(x[curRow][curCol] <= x[curRow][curCol + 1]){
						if(checkRow(x, curRow, curCol + 1, mode) != 1){
							return -1;
						}
						return 1;
					}
					break;
			}
			break;
	}

	return -1;	
}

int checkCol(int **x, int curRow, int curCol, int mode){
	switch(curRow){
		case 3:
			return 1;
			break;
		default:
			// 0 Higher from left to right
			// 1 Higher from right to left
			switch(mode){
				case 0:
					if(x[curRow][curCol] >= x[curRow + 1][curCol]){
						if(checkRow(x, curRow + 1, curCol, mode) != 1){
							return -1;
						}
						return 1;
					} 
					break;
				case 1:
					if(x[curRow][curCol] <= x[curRow + 1][curCol]){
						if(checkRow(x, curRow + 1, curCol, mode) != 1){
							return -1;
						}
						return 1;
					}
					break;
			}
			break;
	}

	return -1;	
}

// int surroundCheck(int **x, int row, int col){
// 	// int highest = getHighestOrSecondHighest(x, row, col, 0);
// 	// int secondHighest = getHighestOrSecondHighest(x, row, col, 1);
// 	int total;
// 	for(int i = 0; i < row; i++){	
//  		for(int j = 0; j < col; j++){
// 	 			if(i != 0){
// 	 				total += (pointReturn(log2(x[i][j]), log2(x[i - 1][j]) ));
// 	 			}

// 	 			if(i != 3){
// 	 				total += (pointReturn(log2(x[i][j]), log2(x[i + 1][j]) ));
// 	 			}

// 	 			if(j != 0){
// 	 				total += (pointReturn(log2(x[i][j]), log2(x[i][j - 1]) ));
// 	 			}

// 	 			if(j != 3){
// 	 				total += (pointReturn(log2(x[i][j]), log2(x[i][j + 1]) ));
// 	 			}
//  		}		
// 	}

// 	return total;
// }

// int pointReturn(int x, int y){
// 	if(x == y){
// 		return 3;
// 	} else if(y == (x - 1)){
// 		return 1;
// 	} else {
// 		return 0;
// 	}
// }

int highestInCorner(int **x, int row, int col, int gradient){
	int temp = getHighestOrSecondHighest(x, row, col, 0);


	switch(gradient){
		case 0:
			if(x[0][0] == temp){
				return 1;
			}
			return -1;
			break;
		case 1:
			if(x[3][0] == temp){
				return 1;
			}
			return -1;
			break;
		case 2:
			if(x[0][3] == temp){
				return 1;
			}
			return -1;
			break;
		case 3:
			if(x[3][3] == temp){
				return 1;
			}
			return -1;
			break;
	}

	return -1;
}


int getHighestOrSecondHighest(int **x, int row, int col, int mode){
	int highest = 0;
	int secondHighest = 0;
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j++){
			if (highest < x[i][j]){
				secondHighest = highest;
				highest = x[i][j];
			} 
		}
	}

	if(mode == 0){
		return highest;
	} else {
		return secondHighest;
	}
	
}

int assignVal(int **x, int row, int col, int newValLocation, int valMode){
	int temp = 0;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(x[i][j] == 0)
				temp++;
			if (temp == newValLocation) {
				switch(valMode){
					case 0:
						x[i][j] = 2;
						break;
					case 1:
						x[i][j] = 4;
						break;
				}				
				return 1;
			}
		}
	}

	return 0;
}