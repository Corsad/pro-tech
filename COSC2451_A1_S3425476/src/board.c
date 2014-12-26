#include <stdio.h>
#include <unistd.h>
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
#define DISTANCE_BETWEEN_BOARD 40
int location = 0;
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

	printMap(x, ROW, COL, location);
	printScore(score,ROW, location);
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
			printMap(x, ROW, COL, location);
			printScore(score,ROW, location);
			printGoal(ROW,goal);
			break;
			case KEY_DOWN:
			clear();
			if (simplifyTest(tests[1],x,ROW, COL)==1) {
				simplify(funcs[1], x , ROW, COL,score);
				randomVal(x,ROW, COL);	
			}
			printMap(x, ROW, COL, location);
			printScore(score,ROW, location);
			printGoal(ROW,goal);
			break;
			case KEY_LEFT:
			clear();
			if (simplifyTest(tests[2],x,ROW, COL)==1) {
				simplify(funcs[2], x , ROW, COL,score);
				randomVal(x,ROW, COL);	
			}
			printMap(x, ROW, COL, location);
			printScore(score,ROW, location);
			printGoal(ROW,goal);
			break;
			case KEY_RIGHT:
			clear();
			if (simplifyTest(tests[3],x,ROW, COL)==1) {
				simplify(funcs[3], x , ROW, COL,score);
				randomVal(x,ROW, COL);	
			}
			printMap(x, ROW, COL, location);
			printScore(score,ROW, location);
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

int playGame2Player(int ROW,int COL){
	clear();

	int *score = malloc(sizeof(int));

	*score = 0;

	int **x = malloc(sizeof(int *) * ROW);

	for(int i = 0; i < ROW; i++){
		x[i] = malloc(sizeof(int) *COL);
	}


	//////// Player 2 ////////

	int *score2 = malloc(sizeof(int));

	*score2 = 0;

	int **x2 = malloc(sizeof(int *) * ROW);

	for(int i = 0; i < ROW; i++){
		x2[i] = malloc(sizeof(int) *COL);
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
			x2[i][j]=0;   
		}
	}

	randomVal(x,ROW, COL);
	randomVal(x,ROW, COL);

////////////////////////////////////

	// Move Arrow map to the right
	location = DISTANCE_BETWEEN_BOARD;

	printMap(x, ROW, COL, location);
	printScore(score,ROW, location);
	location = 0;

	sleep(1);
	randomVal(x2,ROW, COL);
	randomVal(x2,ROW, COL);

	printMap(x2, ROW, COL, location);
	printScore(score2,ROW, location);
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
			break;
			case KEY_DOWN:
			clear();
			if (simplifyTest(tests[1],x,ROW, COL)==1) {
				simplify(funcs[1], x , ROW, COL,score);
				randomVal(x,ROW, COL);	
			}
			break;
			case KEY_LEFT:
			clear();
			if (simplifyTest(tests[2],x,ROW, COL)==1) {
				simplify(funcs[2], x , ROW, COL,score);
				randomVal(x,ROW, COL);	
			}
			break;
			case KEY_RIGHT:
			clear();
			if (simplifyTest(tests[3],x,ROW, COL)==1) {
				simplify(funcs[3], x , ROW, COL,score);
				randomVal(x,ROW, COL);	
			}
			break;

			////// Player 2 //////
			case 'w':
			clear();
			if (simplifyTest(tests[0],x2,ROW, COL)==1) {
				simplify(funcs[0], x2 , ROW, COL,score2);
				randomVal(x2,ROW, COL);
			}	
				break;
			case 's':
			clear();
			if (simplifyTest(tests[1],x2,ROW, COL)==1) {
				simplify(funcs[1], x2 , ROW, COL,score2);
				randomVal(x2,ROW, COL);
			}	
				break;
			case 'a':
			clear();
			if (simplifyTest(tests[2],x2,ROW, COL)==1) {
				simplify(funcs[2], x2 , ROW, COL,score2);
				randomVal(x2,ROW, COL);
			}	
				break;
			case 'd':
			clear();
			if (simplifyTest(tests[3],x2,ROW, COL)==1) {
				simplify(funcs[3], x2 , ROW, COL,score2);
				randomVal(x2,ROW, COL);
			}	
				break;
		}

		location = DISTANCE_BETWEEN_BOARD;
		printMap(x, ROW, COL, location);
		printScore(score,ROW, location);
		location = 0;

		///// Player 2 print/////
		printMap(x2, ROW, COL, location);
		printScore(score2,ROW, location);



		if (moveable(x,ROW,COL)==0 && moveable(x2,ROW,COL)==0) {
			if(score > score2){
				// Need location
				mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 1, 0, "Player 1 win.");
			} else if (score < score2){
				mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 1, 0, "Player 2 win.");
			} else {
				mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 1, 0, "Draw.");
			}
			mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 2, 0, "Press q to go back to menu.");
		}
	}

	for(int i = 0; i < ROW; i++){
		free(x[i]);
		free(x2[i]);
	}

	free(x);	
	free(x2);	

	free(score);
	free(score2);

	return 0;
}

int playGamePlayerVsAI(int ROW,int COL, int (* AIFuncs)(int **, int, int)){
	clear();

	int *score = malloc(sizeof(int));

	*score = 0;

	int **x = malloc(sizeof(int *) * ROW);

	for(int i = 0; i < ROW; i++){
		x[i] = malloc(sizeof(int) *COL);
	}


	//////// Player 2 ////////

	int *score2 = malloc(sizeof(int));

	*score2 = 0;

	int **x2 = malloc(sizeof(int *) * ROW);

	for(int i = 0; i < ROW; i++){
		x2[i] = malloc(sizeof(int) *COL);
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
			x2[i][j]=0;   
		}
	}

	randomVal(x,ROW, COL);
	randomVal(x,ROW, COL);

////////////////////////////////////

	// Move Arrow map to the right
	location = DISTANCE_BETWEEN_BOARD;

	printMap(x, ROW, COL, location);
	printScore(score,ROW, location);
	location = 0;

	sleep(1);
	randomVal(x2,ROW, COL);
	randomVal(x2,ROW, COL);

	printMap(x2, ROW, COL, location);
	printScore(score2,ROW, location);
	int c;

	// simplify(,x,,)
	// x: 1 -> Up; 2 -> Down; 3 -> Left; 4 -> Right;
	
	void (* funcs[4])(int **, int, int,int *) = {&up, &down, &left, &right};
	int (* tests[4])(int **, int, int) = {&upTest,&downTest,&leftTest,&rightTest};

	timeout(200);
	while(((c = getch()) != 'q')){
		switch(c){
			case KEY_UP:
			clear();
			if (simplifyTest(tests[0],x,ROW, COL)==1) {
				simplify(funcs[0], x , ROW, COL,score);
				randomVal(x,ROW, COL);
				c = 'a';
			}			
			break;
			case KEY_DOWN:
			clear();
			if (simplifyTest(tests[1],x,ROW, COL)==1) {
				simplify(funcs[1], x , ROW, COL,score);
				randomVal(x,ROW, COL);	
				c = 'a';
			}
			break;
			case KEY_LEFT:
			clear();
			if (simplifyTest(tests[2],x,ROW, COL)==1) {
				simplify(funcs[2], x , ROW, COL,score);
				randomVal(x,ROW, COL);	
				c = 'a';
			}
			break;
			case KEY_RIGHT:
			clear();
			if (simplifyTest(tests[3],x,ROW, COL)==1) {
				simplify(funcs[3], x , ROW, COL,score);
				randomVal(x,ROW, COL);	
				c = 'a';
			}
			break;
		}

		int temp = AIFuncs(x2, ROW, COL);
			if(moveable(x2,ROW,COL)==1){
				simplify(funcs[temp], x2 , ROW, COL,score2);
				randomVal(x2,ROW, COL);
			}		
			
			if(moveable(x2,ROW,COL)==0){
			timeout(-1);
		}

		location = DISTANCE_BETWEEN_BOARD;
		printMap(x, ROW, COL, location);
		printScore(score,ROW, location);
		location = 0;

		///// Player 2 print/////
		printMap(x2, ROW, COL, location);
		printScore(score2,ROW, location);



		if (moveable(x,ROW,COL)==0 && moveable(x2,ROW,COL)==0) {
			if(score > score2){
				// Need location
				mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 1, 0, "Player 1 win.");
			} else if (score < score2){
				mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 1, 0, "Player 2 win.");
			} else {
				mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 1, 0, "Draw.");
			}
			mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 2, 0, "Press q to go back to menu.");
		}
	}

	for(int i = 0; i < ROW; i++){
		free(x[i]);
		free(x2[i]);
	}

	free(x);	
	free(x2);	

	free(score);
	free(score2);
	timeout(-1);
	return 0;
}

int playGameAIVsAI(int ROW,int COL, int (* AIFuncs)(int **, int, int), int (* AIFuncs2)(int **, int, int)){
	clear();

	int *score = malloc(sizeof(int));

	*score = 0;

	int **x = malloc(sizeof(int *) * ROW);

	for(int i = 0; i < ROW; i++){
		x[i] = malloc(sizeof(int) *COL);
	}


	//////// Player 2 ////////

	int *score2 = malloc(sizeof(int));

	*score2 = 0;

	int **x2 = malloc(sizeof(int *) * ROW);

	for(int i = 0; i < ROW; i++){
		x2[i] = malloc(sizeof(int) *COL);
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
			x2[i][j]=0;   
		}
	}

	randomVal(x,ROW, COL);
	randomVal(x,ROW, COL);

////////////////////////////////////

	// Move Arrow map to the right
	location = DISTANCE_BETWEEN_BOARD;

	printMap(x, ROW, COL, location);
	printScore(score,ROW, location);
	location = 0;

	sleep(1);
	randomVal(x2,ROW, COL);
	randomVal(x2,ROW, COL);

	printMap(x2, ROW, COL, location);
	printScore(score2,ROW, location);
	int c;

	// simplify(,x,,)
	// x: 1 -> Up; 2 -> Down; 3 -> Left; 4 -> Right;
	
	void (* funcs[4])(int **, int, int,int *) = {&up, &down, &left, &right};
	int (* tests[4])(int **, int, int) = {&upTest,&downTest,&leftTest,&rightTest};

	timeout(200);
	while(((c = getch()) != 'q')){
		clear();
		int temp = AIFuncs(x, ROW, COL);
		if(moveable(x,ROW,COL)==1){
			simplify(funcs[temp], x , ROW, COL,score);
			randomVal(x,ROW, COL);
		}		

		temp = AIFuncs2(x2, ROW, COL);	

		if(moveable(x2,ROW,COL)==1){
			simplify(funcs[temp], x2 , ROW, COL,score2);
			randomVal(x2,ROW, COL);
		}	

		if(moveable(x,ROW,COL)==0 && moveable(x2,ROW,COL)==0){
		timeout(-1);
		}	

		location = DISTANCE_BETWEEN_BOARD;
		printMap(x, ROW, COL, location);
		printScore(score,ROW, location);
		location = 0;

		///// Player 2 print/////
		printMap(x2, ROW, COL, location);
		printScore(score2,ROW, location);



		if (moveable(x,ROW,COL)==0 && moveable(x2,ROW,COL)==0) {
			if(score > score2){
				// Need location
				mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 1, 0, "AI 1 win.");
			} else if (score < score2){
				mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 1, 0, "AI 2 win.");
			} else {
				mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 1, 0, "Draw.");
			}
		}
		mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 2, 0, "Press q to go back to menu.");
	}

	for(int i = 0; i < ROW; i++){
		free(x[i]);
		free(x2[i]);
	}

	free(x);	
	free(x2);	

	free(score);
	free(score2);
	timeout(-1);
	return 0;
}

int playGameAI(int ROW,int COL, int (* AIFuncs)(int **, int, int)){
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

	printMap(x, ROW, COL, location);
	printScore(score,ROW, location);
	printGoal(ROW,goal);
	int c;

	
	void (* funcs[4])(int **, int, int,int *) = {&up, &down, &left, &right};
	int (* tests[4])(int **, int, int) = {&upTest,&downTest,&leftTest,&rightTest};
	mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 2, 0, "Press q to go back to menu");

	timeout(200);
	while(c  != 'q' ){
		// Speed
		
		c = getch();
		int temp = AIFuncs(x, ROW, COL);
		clear();
		if(moveable(x,ROW,COL)==1){
			simplify(funcs[temp], x , ROW, COL,score);
			randomVal(x,ROW, COL);
		}		
		
		printMap(x, ROW, COL, location);
		printScore(score,ROW, location);
		printGoal(ROW,goal);
		mvprintw(CELLHEIGHT + ROW * CELLHEIGHT + 2, 0, "Press q to go back to menu");
		if (goalTest(x,ROW,COL,goal)==1 && *goalReached==0) {
			*goalReached = 1;
		}

		if(moveable(x,ROW,COL)==0){
			timeout(-1);
		}
	}

	clear();

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

void printMap(int **x, int row, int col, int location){
	int cellLength = getMaxLength(x, row, col) + 1;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			// mvprintw((CELLHEIGHT + i * CELLHEIGHT), (cellLength + (cellLength*j) - getIntLength(x[i][j])), "%i", x[i][j]);
			coloring(x[i][j]);
			mvprintw((CELLHEIGHT + i * CELLHEIGHT), (5 + (5*j) - getIntLength(x[i][j])) + location, "%i", x[i][j]);
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

void printScore(int *score, int row, int location) {
	mvprintw(CELLHEIGHT + row * CELLHEIGHT, 0 + location, "Score: %i", *score);
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

