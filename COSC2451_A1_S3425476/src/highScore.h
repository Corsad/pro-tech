#ifndef HIGHSCORE
#define HIGHSCORE

#include "player.h"

/** Re-arange the list of struct player base on score
  * @param list arrat of struct player to be changed
  * @param currentLength length of the array
  */
void orderByScore(struct player *list, int currentLength);

/** Print high score based on board size
  * @param row row of the board
  * @param col col of the board
  */
void printHighscore(int row, int col);

/** Open the high score text file and return the array of struct player according to board sizes
  */
void openFile(struct player *list);

/** Write to the high score text file
  * @param list array of struct player that is going to be writen
  */
void writeToFile(struct player *list);

/** Return the lowest score from the list
  * @param list array of struct player
  */
int getLowestScore(struct player *list);

/** Return the amount of character from the longest name
  * @param list array of struct player
  */
int getMaxNameLength(struct player* list);

/** Ask user for high score, depend on the score it may not asked at all

  * @param position the question will be printed on this row
  * @param score user score
  * @param row row of the board user got high score
  * @param col col of the board user got high score
  */
void askHighScore(int position, int score, int row, int col);

/** Return the amount of character from the longest score
  * @param list array of struct player
  */

int getMaxScoreLength(struct player* list);

/** Replace all space when user typed in with "_"
  * @param name the name the user typed in
  */
void replaceSpace(char * name);

/* create new player based on struct player
 * @param name name of the player
 * @param score score the player has
 * @param day day the player make new high score
 * @param month month the player make new high score
 * @param year year the player make new high score
 * @param row row number of the board the player make new high score
 * @param col column number of the board the player make new high score
 */
struct player createPlayer(char *name, int score, int day, int month, int year,int row, int col);


#endif
