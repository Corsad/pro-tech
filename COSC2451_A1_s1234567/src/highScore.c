#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "player.h"
#include "highScore.h"

#define NAMELENGTH 60
#define LISTLENGTH 10

static int currentLength;

void printHighscore(){
	clear();

	struct player *list;

	list = openFile();
	orderByRank(list, 3);

	for (int i = 0; i < currentLength; ++i)
	{
		if(list[i].name != NULL){
			mvprintw(i, 0, "%i %s\t%i", list[i].rank, list[i].name, list[i].score);
		}
	}

	// for (int i = 0; i < LISTLENGTH; ++i)
	// {
	// 	player_free(&list[i]);
	// }

	int c;	
	while(((c = getch()) != 'q')){

	}
	free(name);
	free(list);
}

void orderByRank(struct player *list, int currentLength){
	for (int i = 0; i < currentLength; ++i)
	{
		for (int j = 0; j < currentLength; ++j)
		{
			if(list[i].rank < list[j].rank){
			struct player temp = list[i];
			list[i] = list[j];
			list[j] = temp;
			}				
		}
	}
}

void writeToFile(struct player *list){
	FILE *file = fopen ( "playerScore.txt", "w+" );

	if ( file != NULL ){		
		for (int i = 0; i < currentLength; ++i)
		{
			fprintf(file, "%s\t%i\t%i\n", list[i].name, list[i].score, list[i].rank);
		}
	}

	fclose(file);	
}

struct player * openFile(){
	static const char filename[] = "playerScore.txt";
	char *name = malloc(sizeof(char) * NAMELENGTH);
	int score, rank;

	struct player *list = malloc(sizeof(struct player) * LISTLENGTH);

	currentLength = 0;

	FILE *file = fopen ( filename, "r" );
	if ( file != NULL ){		
		while (fscanf(file, "%s\t%i\t%i", name, &score, &rank) != EOF) {
		  	list[currentLength] = *createPlayer(name, score, rank);
		  	currentLength++;
		}		
	}

	free(name);
	fclose(file);	
	return list;
}

void testHighScore(){
	int score = 5000;
	char * name = malloc(sizeof(char) * NAMELENGTH);
	int rank = 5;


	mvprintw(0, 0, "Score: %i", score);
  	mvprintw(1, 0, "Enter Your Name: ");
	(void) echo();
	getstr(name);
	(void) noecho();
	mvprintw(4, 0, "Press 'q' to quit.");


	struct player testPlayer = *createPlayer(name, score, rank);

	struct player *list = malloc(sizeof(struct player) * LISTLENGTH);
	list = openFile();


	list[currentLength] = testPlayer;
	currentLength++;

	writeToFile(list);

	int c;
	while(((c = getch()) != 'q')){
	}

	free(name);
	free(list);
}

void arrangeScore(struct player *list){
	for (int i = 0; i < LISTLENGTH; ++i)
	{
		// if()
	}
}