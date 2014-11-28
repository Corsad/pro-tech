#ifndef PLAYER
#define PLAYER

#define NAMELENGTH 60

struct player {
    char name[NAMELENGTH];
    int score;
    int day,month,year;
};

/* create new player based on struct player
 * @param name name of the player
 * @param score score the player has
 * @param day day the player make new high score
 * @param month month the player make new high score
 * @param year year the player make new high score
 */
struct player * createPlayer(char *name, int score, int day, int month, int year);

#endif
