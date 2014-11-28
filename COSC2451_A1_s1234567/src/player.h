#ifndef PLAYER
#define PLAYER

#define NAMELENGTH 60

struct player {
    char name[NAMELENGTH];
    int score;
    int day,month,year,row,col;
};

/* create new player based on struct player
 * @param name name of the player
 * @param score score the player has
 * @param day day the player make new high score
 * @param month month the player make new high score
 * @param year year the player make new high score
 * @param row row number of the board the player make new high score
 * @param col column number of the board the player make new high score
 */
struct player * createPlayer(char *name, int score, int day, int month, int year,int row, int col);

#endif
