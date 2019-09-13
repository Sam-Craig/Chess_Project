#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chess_util.h"

const int scorearr[13] = {10,9,5,3,3,1,0,1,3,3,5,9,10};

char inttopiece(int piece)
{
    switch (piece)
    {
    case -6:
        return 'k';
    case -5:
        return 'q';
    case -4:
        return 'r';
    case -3:
        return 'b';
    case -2:
        return 'n';
    case -1:
        return 'p';
    case 0:
        //empty tile labelled with '-
        return '-';
    case 1:
        return 'P';
    case 2:
        return 'N';
    case 3:
        return 'B';
    case 4:
        return 'R';
    case 5:
        return 'Q';
    case 6:
        return 'K';
    }
    //X if something incorrect gets put in one of the squares.
    return 'X';
}

void printboard(board toprint)
{   
    printf("   A|B|C|D|E|F|G|H\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%d  %c", i, inttopiece(toprint.arr[i][0]));
        for (int j = 1; j < 8; j++)
        {
            printf("|%c", inttopiece(toprint.arr[i][j]));
        }
        printf("\n");
    }
}

board *initboard()
{
    board *newboard = malloc(sizeof(board));
    int array[8][8] = {
        {W_ROOK, W_KNIGHT, W_BISHOP, W_QUEEN, W_KING, W_BISHOP, W_KNIGHT, W_ROOK},
        {W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN},
        {BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK},
        {BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK},
        {BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK},
        {BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK},
        {B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN},
        {B_ROOK, B_KNIGHT, B_BISHOP, B_QUEEN, B_KING, B_BISHOP, B_KNIGHT, B_ROOK}
    };
    memcpy(newboard -> arr, array, sizeof(array));
    return newboard;
}


//ToDo: Make testlegal work. Returns 0 if functions executes
int movepiece(board * game, int xinit, int yinit, int xdest, int ydest, int test) 
{
    if (test && testlegal(game, xinit, yinit, xdest, ydest)) 
        return 1;
    int piece = game->arr[yinit][xinit];
    game->arr[ydest][xdest] = piece;
    game->arr[yinit][xinit] = 0;
    return 0;
}

// Returns NULL if move fails, otherwise returns an array: {x init, y init, x dest, y dest, check}
// check is 1 if the other side is in check, otherwise 0
int * outermovepiece(board * game, int xinit, int yinit, int xdest, int ydest, int side) 
{
    if (movepiece(game, xinit, yinit, xdest, ydest, 1))
        return NULL;

    int * ret = malloc(5*sizeof(int));
    if (ret == NULL) {
        fprintf(stderr, "Malloc failed");
        exit(1);
    }
    ret[0] = xinit;
    ret[1] = yinit;
    ret[2] = xdest;
    ret[3] = ydest;
    ret[4] = incheck(*game, -side);
    return ret;
}

// Returns 0 if the move is legal, otherwise returns 1
int testlegal(board * game, int xinit, int yinit, int xdest, int ydest) 
{
    return 0;
}

// Returns 0 if not in check, otherwise returns 1
int incheck(board game, int side){
    return 0;
}

// Returns 0 if not in checkmate, otherwise returns 1
int incheckmate(board game, int side) {
    return 0;
}