#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include <math.h>

#include "board.h"
#include "random.h"
#include "move.h"
#include "moveable.h"
#include "highScore.h"
#include "pt_utils.h"
#include "drawMenu.h"
#include "khanhAI.h"

#define CELLHEIGHT 3

int playGame(int ROW,int COL){
	clear();

	int *score = malloc(sizeof(int));

	*score = 0;

	int *goal = malloc(sizeof(int));

	*goal = goalCal(ROW);

	int *goalReached = malloc(sizeof(int));

	*goalReached = 0;

	int **x = malloc(sizeof(int *) * ROW);

	for(int i = 0; i < ROW; i++){
		x[i] = malloc(sizeof(int) *COL);
	}

////////////////////////////////////
	// //There are 2 map: map.txt and map2.txt
	// FILE *f = fopen("map4.txt", "r");
	// for(int i = 0; i < ROW; i++){
	// 	for(int j = 0; j < COL;j++){
	// 		// printf("x[%i][%i]: ",i,j);
	// 		// scanf("%i",&x[i][j]);
	// 		fscanf (f, "%i", &x[i][j]);   
	// 	}
	// }
	// fclose (f);     
////////////////////////////////////
	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL;j++){
			// printf("x[%i][%i]: ",i,j);
			// scanf("%i",&x[i][j]);
			x[i][j]=0;   
		}
	}

	randomVal(x,ROW, COL);
	randomVal(x,ROW, COL);
////////////////////////////////////

	printMap(x, ROW, COL);
	printScore(score,ROW);
	printGoal(ROW,goal);
	int c;

	// simplify(,x,,)
	// x: 1 -> Up; 2 -> Down; 3 -> Left; 4 -> Right;
	
	void (* funcs[4])(int **, int, int,int *) = {&up, &down, &left, &right};
	int (* tests[4])(int **, int, int) = {&upTest,&downTest,&leftTest,&rightTest};

	while(((c = getch()) != 'q')){
		switch(c){
			case KEY_UP:
			clear();
			if (simplifyTest(tests[0],x,ROW, COL)==1) {
				simplify(funcs[0], x , ROW, COL,score);
				randomVal(x,ROW, COL);

			}
			printMap(x, ROW, COL);
			printScore(score,ROW);
			printGoal(ROW,goal);
			break;
			case KEY_DOWN:
			clear();
			if (simplifyTest(tests[1],x,ROW, COL)==1) {
				simplify(funcs[1], x , ROW, COL,score);
				randomVal(x,ROW, COL);	
			}
			printMap(x, ROW, COL);
			printScore(score,ROW);
			printGoal(ROW,goal);
			break;
			case KEY_LEFT:
			clear();
			if (simplifyTest(tests[2],x,ROW, COL)==1) {
				simplify(funcs[2], x , ROW, COL,score);
				randomVal(x,ROW, COL);	
			}
			printMap(x, ROW, COL);
			printScore(score,ROW);
			printGoal(ROW,goal);
			break;
			case KEY_RIGHT:
			clear();
			if (simplifyTest(tests[3],x,ROW, COL)==1) {
				simplify(funcs[3], x , ROW, COL,score);
				randomVal(x,ROW, COL);	
			}
			printMap(x, ROW, COL);
			printScore(score,ROW);
			printGoal(ROW,goal);
			break;
		}
		printBestMove(x, ROW, COL);
		if (goalTest(x,ROW,COL,goal)==1 && *goalReached==0) {
			*goalReached = 1;
		}

		if (moveable(x,ROW,COL)==0) {
			printOver(ROW);
			askHighScore(CELLHEIGHT + ROW * CELLHEIGHT + 3,*score,ROW,COL);
			break;
		} else if (*goalReached==1) {
			printGoalReached(ROW,goal);
		}
	}

	for(int i = 0; i < ROW; i++){
		free(x[i]);
	}

	free(x);	

	free(goal);

	free(score);

	free(goalReached);

	return 0;
}

int playGameAI(int ROW,int COL){
	clear();

	int *score = malloc(sizeof(int));

	*score = 0;

	int *goal = malloc(sizeof(int));

	*goal = goalCal(ROW);

	int *goalReached = malloc(sizeof(int));

	*goalReached = 0;

	int **x = malloc(sizeof(int *) * ROW);

	for(int i = 0; i < ROW; i++){
		x[i] = malloc(sizeof(int) *COL);
	}

	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL;j++){
			x[i][j]=0;   
		}
	}

	randomVal(x,ROW, COL);
	randomVal(x,ROW, COL);

	printMap(x, ROW, COL);
	printScore(score,ROW);
	printGoal(ROW,goal);
	int c;

	
	void (* funcs[4])(int **, int, int,int *) = {&up, &down, &left, &right};
	int (* tests[4])(int **, int, int) = {&upTest,&downTest,&leftTest,&rightTest};
	mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 2, 0, "Press q to go back to menu");


	while(c  != 'q' ){
		// Speed
		timeout(200);
		c = getch();
		int temp = getHighestScore(x, ROW, COL);
		clear();
		if(moveable(x,ROW,COL)==1){
			simplify(funcs[temp], x , ROW, COL,score);
			randomVal(x,ROW, COL);
		}		
		
		printMap(x, ROW, COL);
		printScore(score,ROW);
		printGoal(ROW,goal);
		mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 2, 0, "Press q to go back to menu");
		if (goalTest(x,ROW,COL,goal)==1 && *goalReached==0) {
			*goalReached = 1;
		}

		if(moveable(x,ROW,COL)==0){
			timeout(-1);
		}
	}


	for(int i = 0; i < ROW; i++){
		free(x[i]);
	}

	free(x);	

	free(goal);

	free(score);

	free(goalReached);

	timeout(-1);
	return 0;

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
			coloring(x[i][j]);
			mvprintw((CELLHEIGHT + i * CELLHEIGHT), (5 + (5*j) - getIntLength(x[i][j])), "%i", x[i][j]);
		}
	}
	coloring(0);
}

void coloring(int x){
	switch(x){
		case 2:
			attron(COLOR_PAIR(2));
		break;
		case 4:
			attron(COLOR_PAIR(3));
		break;
		case 8:
			attron(COLOR_PAIR(4));
		break;
		case 16:
			attron(COLOR_PAIR(5));
		break;
		case 32:
			attron(COLOR_PAIR(6));
		break;
		case 64:
			attron(COLOR_PAIR(7));
		break;
		case 128:
			attron(COLOR_PAIR(1));
		break;
		case 256:
			attron(COLOR_PAIR(2));
		break;
		case 512:
			attron(COLOR_PAIR(3));
		break;
		case 1024:
			attron(COLOR_PAIR(4));
		break;
		case 2048:
			attron(COLOR_PAIR(5));
		break;
		case 4096:
			attron(COLOR_PAIR(6));
		break;
		case 8192:
			attron(COLOR_PAIR(7));
		break;
		default:
			attron(COLOR_PAIR(1));
		break;
	}
}

void printScore(int *score, int row) {
	mvprintw(CELLHEIGHT + row * CELLHEIGHT, 0, "Score: %i", *score);
}


void printGoal(int row, int *goal) {
	mvprintw(CELLHEIGHT + row * CELLHEIGHT + 1, 0, "Goal: get to the %i tile", *goal);
}

void printGoalReached(int row, int *goal) {
	mvprintw(CELLHEIGHT + row * CELLHEIGHT + 2, 0, "Congratulations! You reached the %i tile. You can continue playing.", *goal);
}

void printOver(int row) {
	mvprintw(CELLHEIGHT + row * CELLHEIGHT + 2, 0, "No more moves! Game over.");
}

