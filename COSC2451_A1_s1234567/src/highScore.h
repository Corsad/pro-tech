#ifndef HIGHSCORE
#define HIGHSCORE

#include "player.h"
void orderByRank(struct player *list, int currentLength);
void printHighscore();
void testHighScore();
struct player * openFile();
void writeToFile(struct player *list);

#endif
