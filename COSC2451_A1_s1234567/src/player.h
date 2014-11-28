#ifndef PLAYER
#define PLAYER

#define NAMELENGTH 60

struct player {
    char name[NAMELENGTH];
    int score;
    int day,month,year,row,col;
};

struct player * createPlayer(char *name, int score, int day, int month, int year,int row, int col);

void player_free(struct player *player);

#endif
