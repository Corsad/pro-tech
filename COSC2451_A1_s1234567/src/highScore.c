#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>

#include "player.h"
#include "highScore.h"
#include "pt_utils.h"

#define NAMELENGTH 60
#define TOP 10
#define LISTLENGTH 30 //depending on available board sizes. We have 3 so 3 top-tens = 30

static int currentLength;

void printHighscore(int row, int col){
	clear();
	struct player *list = malloc(sizeof(struct player) * LISTLENGTH); //full list of player from file
	struct player *listByBoard=malloc(sizeof(struct player) * TOP); //list of player by board sizes
	int count = 0;//Keep track of listByBoard
	
	openFile(list);	

	mvprintw(0, 0, "RANK");
	mvprintw(0, 5, "NAME");
	mvprintw(0, getMaxNameLength(list)+ 6, "SCORE");
	mvprintw(0, getMaxScoreLength(list)+ getMaxNameLength(list) + 7 , "DATE");
	
	for (int i = 0; i < currentLength; ++i)
	{
		if(list[i].row==row&&list[i].col==col){
			listByBoard[count] = list [i];
			count++;
		}
	}


	for (int i = 0; i < count; ++i)
	{
		int maxLength = getMaxNameLength(listByBoard)+ 6;
		if(listByBoard[i].name != NULL){
			mvprintw(i+ 2, 0, "%i", i + 1);
			mvprintw(i+ 2, 5, "%s", listByBoard[i].name);
			mvprintw(i+ 2, maxLength, "%i", listByBoard[i].score);
			mvprintw(i+ 2, maxLength + getMaxScoreLength(listByBoard) + 1, "%i-%i-%i", listByBoard[i].day, listByBoard[i].month, listByBoard[i].year);
		}
	}

	mvprintw(count + 3, 0, "Press \'q\' to go back to menu.");

	int c;	
	while(((c = getch()) != 'q')){

	}
	free(listByBoard);
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
			fprintf(file, "%s\t%i\t%i-%i-%i\t%i\t%i\n", list[i].name, list[i].score,list[i].day,list[i].month,list[i].year,list[i].row,list[i].col);
		}
	}

	fclose(file);	
}

void openFile(struct player *list){
	static const char filename[] = "playerScore.txt";
	char *name = malloc(sizeof(char) * NAMELENGTH);
	int score, day, month, year, row, col;

	currentLength = 0;

	FILE *file = fopen ( filename, "r" );
	if ( file != NULL ){		
		while (fscanf(file, "%s\t%i\t%i-%i-%i\t%i\t%i\n", name, &score, &day, &month, &year,&row,&col) != EOF) {
		  	list[currentLength] = createPlayer(name, score, day, month, year,row,col);
		  	currentLength++;
		  }
	}

	orderByScore(list, currentLength);

	free(name);
	fclose(file);	
}

void askHighScore(int position, int score, int row, int col){

	struct player *list = malloc(sizeof(struct player) * LISTLENGTH);
	struct player *listByBoard=malloc(sizeof(struct player) * TOP);
	int count = 0;
	openFile(list);
	char * name = malloc(sizeof(char) * NAMELENGTH);

	for (int i = 0; i < currentLength; ++i)
	{
		if(list[i].row==row&&list[i].col==col){
			listByBoard[count] = list [i];
			count++;
		}
	}

	if(count != TOP){
		(void) echo();
		keypad(stdscr, FALSE);
		do{
			mvprintw(position, 0, "Enter Your Name: ");
			getstr(name);
		} while(strlen(name) == 0);
		
		keypad(stdscr, TRUE);
		(void) noecho();
		mvprintw(position + 2, 0, "Press \'q\' to go back to menu.");



		time_t t = time(NULL);
    	struct tm tm = *localtime(&t);
    	replaceSpace(name);
		struct player testPlayer = createPlayer(name, score, tm.tm_mday, tm.tm_mon + 1, tm.tm_year  + 1900,row,col);

		// struct player *list = malloc(sizeof(struct player) * LISTLENGTH);
		// list = openFile();


		list[currentLength] = testPlayer;
		currentLength++;

		writeToFile(list);

		int c;
		while(((c = getch()) != 'q')){
		}	
	} else if(score > getLowestScore(listByBoard)){
		(void) echo();
		keypad(stdscr, FALSE);
		do{
			mvprintw(position, 0, "Enter Your Name: ");
			getstr(name);
		} while(strlen(name) == 0);
		keypad(stdscr, TRUE);
		(void) noecho();
		mvprintw(position + 2, 0, "Press \'q\' to go back to menu.");


		time_t t = time(NULL);
    	struct tm tm = *localtime(&t);

    	replaceSpace(name);
		struct player testPlayer = createPlayer(name, score, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,row,col);

		// struct player *list = malloc(sizeof(struct player) * LISTLENGTH);
		// list = openFile();

		count = 0;
		for (int i = 0; i < currentLength; ++i)
		{
			if(list[i].row==row&&list[i].col==col){
				count++;
				if (count==TOP)
					list[i]=testPlayer;
			}
		}

		writeToFile(list);

		int c;
		while(((c = getch()) != 'q')){
		}	
	} else {
		mvprintw(position + 1, 0, "Press \'q\' to go back to menu.");
		int c;
		while(((c = getch()) != 'q')){
		}	
	}

	free(name);
	free(listByBoard);
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

struct player createPlayer(char *name, int score, int day, int month, int year, int row, int col) {

    struct player newPlayer;
    
    strcpy(newPlayer.name, name);
    newPlayer.score = score;
    newPlayer.day = day;
    newPlayer.month = month;
    newPlayer.year = year;    
    newPlayer.row = row;
    newPlayer.col = col;
    
    return newPlayer;
}