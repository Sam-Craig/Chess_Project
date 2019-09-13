#ifndef CHESS_CPU_H

#include "chess_util.h"

#define CHESS_CPU_H

#define MOVE_ARR_SIZE 140
#define MOVE_INFO_ARR_SIZE 5

// This is a 140x5 array.
typedef int moveinfoarr[MOVE_INFO_ARR_SIZE];

typedef struct{
    moveinfoarr movearr[MOVE_ARR_SIZE];
    int cur;
} pmoves;

void printpossiblemoves(pmoves *possiblemoves, board game);

pmoves* getlegalmoves(board game, int side);

void pawnlegalmoves(board game, pmoves * moves, int x, int y, int side);

void knightlegalmoves(board game, pmoves * moves, int x, int y, int side);

void bishoplegalmoves(board game, pmoves * moves, int x, int y, int side);

void rooklegalmoves(board game, pmoves * moves, int x, int y, int side);

void queenlegalmoves(board game, pmoves * moves, int x, int y, int side);

void kinglegalmoves(board game, pmoves * moves, int x, int y, int side);

int checkaroundking(board game, int * around, int x, int y, int side);

void insert_pmove(pmoves *moves, board game, int curx, int cury, int newx, int newy);

#endif
