#ifndef PLAYER
#define PLAYER

#define NAMELENGTH 60

struct player {
    char name[NAMELENGTH];
    int score;
};

struct player * createPlayer(char *name, int score);

void player_free(struct player *player);

#endif
