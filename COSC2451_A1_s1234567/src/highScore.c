#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>

#include "player.h"
#include "highScore.h"
#include "pt_utils.h"

#define NAMELENGTH 60
#define LISTLENGTH 10

static int currentLength;

void printHighscore(){
	clear();
	struct player *list;

	list = openFile();	

	mvprintw(0, 0, "RANK");
	mvprintw(0, 5, "NAME");
	mvprintw(0, getMaxNameLength(list)+ 6, "SCORE");
	mvprintw(0, getMaxScoreLength(list)+ getMaxNameLength(list) + 7 , "DATE");
	for (int i = 0; i < currentLength; ++i)
	{
		int maxLength = getMaxNameLength(list)+ 6;
		if(list[i].name != NULL){
			mvprintw(i+ 2, 0, "%i", i + 1);
			mvprintw(i+ 2, 5, "%s", list[i].name);
			mvprintw(i+ 2, maxLength, "%i", list[i].score);
			mvprintw(i+ 2, maxLength + getMaxScoreLength(list) + 1, "%i-%i-%i", list[i].day, list[i].month, list[i].year);
		}
	}

	mvprintw(currentLength + 3, 0, "Press \'q\' to go back to menu.");

	int c;	
	while(((c = getch()) != 'q')){

	}
	free(list);
}

void orderByScore(struct player *list, int currentLength){
	for (int i = 0; i < currentLength; ++i)
	{
		for (int j = 0; j < currentLength; ++j)
		{
			if(list[i].score > list[j].score){
			struct player temp = list[i];
			list[i] = list[j];
			list[j] = temp;
			}				
		}
	}
}

void writeToFile(struct player *list){
	FILE *file = fopen ( "playerScore.txt", "w+" );
	orderByScore(list, currentLength);

	if ( file != NULL ){		
		for (int i = 0; i < currentLength; ++i)
		{
			fprintf(file, "%s\t%i\t%i-%i-%i\n", list[i].name, list[i].score,list[i].day,list[i].month,list[i].year);
		}
	}

	fclose(file);	
}

struct player * openFile(){
	static const char filename[] = "playerScore.txt";
	char *name = malloc(sizeof(char) * NAMELENGTH);
	int score, day, month, year;

	struct player *list = malloc(sizeof(struct player) * LISTLENGTH);

	currentLength = 0;

	FILE *file = fopen ( filename, "r" );
	if ( file != NULL ){		
		while (fscanf(file, "%s\t%i\t%i-%i-%i", name, &score, &day, &month, &year) != EOF) {
		  	list[currentLength] = *createPlayer(name, score, day, month, year);
		  	currentLength++;
		}		
	}

	orderByScore(list, currentLength);

	free(name);
	fclose(file);	
	return list;
}

void askHighScore(int row, int score){
	struct player *list = malloc(sizeof(struct player) * LISTLENGTH);
	list = openFile();
	char * name = malloc(sizeof(char) * NAMELENGTH);

	if(currentLength != 10){
		(void) echo();
		keypad(stdscr, FALSE);
		do{
			mvprintw(row, 0, "Enter Your Name: ");
			getstr(name);
		} while(strlen(name) == 0);
		
		keypad(stdscr, TRUE);
		(void) noecho();
		mvprintw(row + 2, 0, "Press \'q\' to go back to menu.");



		time_t t = time(NULL);
    	struct tm tm = *localtime(&t);
    	replaceSpace(name);
		struct player testPlayer = *createPlayer(name, score, tm.tm_mday, tm.tm_mon + 1, tm.tm_year  + 1900);

		// struct player *list = malloc(sizeof(struct player) * LISTLENGTH);
		// list = openFile();


		list[currentLength] = testPlayer;
		currentLength++;

		writeToFile(list);

		int c;
		while(((c = getch()) != 'q')){
		}	
	} else if(score > getLowestScore(list)){
		(void) echo();
		keypad(stdscr, FALSE);
		do{
			mvprintw(row, 0, "Enter Your Name: ");
			getstr(name);
		} while(strlen(name) == 0);
		keypad(stdscr, TRUE);
		(void) noecho();
		mvprintw(row + 2, 0, "Press \'q\' to go back to menu.");


		time_t t = time(NULL);
    	struct tm tm = *localtime(&t);

    	replaceSpace(name);
		struct player testPlayer = *createPlayer(name, score, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

		// struct player *list = malloc(sizeof(struct player) * LISTLENGTH);
		// list = openFile();


		list[9] = testPlayer;

		writeToFile(list);

		int c;
		while(((c = getch()) != 'q')){
		}	
	} else {
		mvprintw(row, 0, "You suck, hard. ");
		mvprintw(row + 2, 0, "Press \'q\' to go back to menu.");
		int c;
		while(((c = getch()) != 'q')){
		}	
	}

	free(name);
	free(list);
}

void testHighScore(){
	struct player *list = malloc(sizeof(struct player) * LISTLENGTH);
	list = openFile();
	int *score = malloc(sizeof(int));
	char * name = malloc(sizeof(char) * NAMELENGTH);


	mvprintw(0, 0, "Score: ");
	(void) echo();
	scanw("%i",score);
	if(currentLength != 10){
		// mvprintw(0, 0, "Score: ");
		// (void) echo();
		// scanw("%i",score);
	  	mvprintw(1, 0, "Enter Your Name: ");
		getstr(name);
		(void) noecho();
		mvprintw(4, 0, "Press \'q\' to go back to menu.");

		time_t t = time(NULL);
    	struct tm tm = *localtime(&t);

		struct player testPlayer = *createPlayer(name, *score, tm.tm_mday, tm.tm_mon + 1, tm.tm_year  + 1900);

		// struct player *list = malloc(sizeof(struct player) * LISTLENGTH);
		// list = openFile();


		list[currentLength] = testPlayer;
		currentLength++;

		writeToFile(list);

		int c;
		while(((c = getch()) != 'q')){
		}	
	} else if(*score > getLowestScore(list)){
		mvprintw(1, 0, "Enter Your Name: ");
		getstr(name);
		(void) noecho();
		mvprintw(4, 0, "Press \'q\' to go back to menu.");


		time_t t = time(NULL);
    	struct tm tm = *localtime(&t);

		struct player testPlayer = *createPlayer(name, *score, tm.tm_mday, tm.tm_mon + 1, tm.tm_year  + 1900);

		// struct player *list = malloc(sizeof(struct player) * LISTLENGTH);
		// list = openFile();


		list[9] = testPlayer;

		writeToFile(list);

		int c;
		while(((c = getch()) != 'q')){
		}	
	} else {
		mvprintw(3, 0, "You suck, hard. ");
		int c;
		while(((c = getch()) != 'q')){
		}	
	}

	free(score);
	free(name);
	free(list);
}

int getLowestScore(struct player *list){
	int temp = list[0].score;
	for (int i = 1; i < currentLength; ++i)
	{
		if(temp > list[i].score){
			temp = list[i].score;
		}
	}

	return temp;
}

int getMaxNameLength(struct player* list){ 
	int temp = strlen(list[0].name);
	for (int i = 1; i < currentLength; ++i)
	{
		if(temp < strlen(list[i].name)){
			temp = strlen(list[i].name);
		}
	}	
	if(temp < 4){
		return 4;
	}
	return temp;
}

int getMaxScoreLength(struct player* list){
	int temp = getIntLength(list[0].score);
	for(int i = 0; i < currentLength; i++){
		if(temp < getIntLength(list[i].score)){
			temp = getIntLength(list[i].score);
		}
	}

	if (temp < 5){
		return 5;
	}
	return temp;
}

void replaceSpace(char * name){
	for (int i = 0; i < strlen(name); ++i)
	{
		if(name[i] == ' '){
			name[i] = '_';
		}
	}
}