#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"

struct player * createPlayer(char *name, int score, int day, int month, int year) {

    struct player *newPlayer = malloc(sizeof(struct player));
    
    strcpy(newPlayer->name, name);
    newPlayer->score = score;
    newPlayer->day = day;
    newPlayer->month = month;
    newPlayer->year = year;    
    
    return newPlayer;
}

void player_free(struct player *player) {

    if (player != NULL) {
        free(player);
    }
}