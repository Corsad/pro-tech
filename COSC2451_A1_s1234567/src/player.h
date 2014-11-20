#ifndef PLAYER
#define PLAYER

#define NAMELENGTH 60

struct player {
    char name[NAMELENGTH];
    int score;
    int rank;
};

struct player * createPlayer(char *name, int score, int rank);

void player_free(struct player *player);

#endif
