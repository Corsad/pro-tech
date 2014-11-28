#ifndef HIGHSCORE
#define HIGHSCORE

#include "player.h"
void orderByScore(struct player *list, int currentLength);
void printHighscore(int row, int col);
struct player * openFile();
void writeToFile(struct player *list);
int getLowestScore(struct player *list);
int getMaxNameLength(struct player* list);
void askHighScore(int position, int score, int row, int col);
int getMaxScoreLength(struct player* list);
void replaceSpace(char * name);

#endif
