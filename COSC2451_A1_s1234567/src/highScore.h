#ifndef HIGHSCORE
#define HIGHSCORE

#include "player.h"
void orderByScore(struct player *list, int currentLength);
void printHighscore();
void testHighScore();
struct player * openFile();
void writeToFile(struct player *list);
int getLowestScore(struct player *list);
int getMaxNameLength(struct player* list);
void askHighScore(int row, int score);
int getMaxScoreLength(struct player* list);
void replaceSpace(char * name);

#endif
