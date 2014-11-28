#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"

struct player * createPlayer(char *name, int score, int day, int month, int year, int row, int col) {

    struct player *newPlayer = malloc(sizeof(struct player));
    
    strcpy(newPlayer->name, name);
    newPlayer->score = score;
    newPlayer->day = day;
    newPlayer->month = month;
    newPlayer->year = year;    
    newPlayer->row = row;
    newPlayer->col = col;
    
    return newPlayer;
}

void player_free(struct player *player) {

    if (player != NULL) {
        free(player);
    }
}