#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "player.h"

#define NAMELENGTH 60
#define LISTLENGTH 10

void orderByRank(struct player *list, int currentLength);
void printHighscore(){
	clear();

	static const char filename[] = "playerScore.txt";
	FILE *file = fopen ( filename, "r" );
	char *name = malloc(sizeof(char) * NAMELENGTH);
	int score, rank;

	struct player list[LISTLENGTH];

	int currentLength = 0;
	if ( file != NULL ){		
		while (fscanf(file, "%s\t%i\t%i", name, &score, &rank) != EOF) {
		  	list[currentLength] = *createPlayer(name, score, rank);
		  	currentLength++;
		}		
	}

	orderByRank(list, currentLength);

	for (int i = 0; i < currentLength; ++i)
	{
		mvprintw(list[i].rank - 1, 0, "%i %s\t%i", list[i].rank, list[i].name, list[i].score);
	}

	// for (int i = 0; i < LISTLENGTH; ++i)
	// {
	// 	player_free(&list[i]);
	// }

	int c;	
	while(((c = getch()) != 'q')){

	}
	free(name);
	fclose(file);	
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