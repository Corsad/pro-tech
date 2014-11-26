#ifndef PLAYER
#define PLAYER

#define NAMELENGTH 60

struct player {
    char name[NAMELENGTH];
    int score;
    int day,month,year;
};

struct player * createPlayer(char *name, int score, int day, int month, int year);

void player_free(struct player *player);

#endif
