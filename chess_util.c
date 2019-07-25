#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chess_util.h"

int scorearr[13] = {10,9,5,3,3,1,0,1,3,3,5,9,10};

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
    board *newboard = (board *) malloc(sizeof(board));
    int array[8][8] = {
        {4, 2, 3, 5, 6, 3, 2, 4},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-4, -2, -3, -5, -6, -3, -2, -4}
    };
    memcpy(newboard -> arr, array, sizeof(array));
    return newboard;
}


//ToDo: Make testlegal work
void movepiece(board *game, int xinit, int yinit, int xdest, int ydest, int testlegal) {
    int piece = game->arr[yinit][xinit];
    game->arr[ydest][xdest] = piece;
    game->arr[yinit][xinit] = 0;
}

//gets all legal moves for a side with given board. Stores it in a 2d array of the form [[piecexloc, pieceyloc, destxloc, destyloc, points]...] with space for all possible moves 32 moves for pawns, 28 moves for rooks, 16 moves for knights, 28 moves for bishops, 28 moves for queen, 8 moves for king = 140 possible moves

//side:1 = white, -1 = black

movearr getlegalmoves(board game, int side)
{
    movearr possiblemoves;
    int cur = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            //if the tile contains a pawn of the correct side
            if (game.arr[i][j] == side * 1) {
                cur = pawnlegalmoves(game, possiblemoves, cur, i, j, side); 
            }
            else if (game.arr[i][j] == side * 2) {
                // cur = knightlegalmoves(game, possiblemoves, cur, i, j, side);
            }
            else if (game.arr[i][j] == side * 3)
            {
                // cur = bishoplegalmoves(game, possiblemoves, cur, i, j, side);
            }
            else if (game.arr[i][j] == side * 4)
            {
                // cur = rooklegalmoves(game, possiblemoves, cur, i, j, side);
            }
            else if (game.arr[i][j] == side * 5)
            {
                // cur = queenlegalmoves(game, possiblemoves, cur, i, j, side);
            }
            else if (game.arr[i][j] == side * 6)
            {
                // cur = kinglegalmoves(game, possiblemoves, cur, i, j, side);
            }
        }
    }
    return possiblemoves;
}

//ToDo: Add promotion
int pawnlegalmoves(board game, movearr moves, int cur, int x, int y, int side) {
    //This might be doable without considering which side we are on using multiplication with side
    if (side == 1) {
        //piece forward and to the right. Tests if there is space to the right and forward of the pawn and if the space has an opposing piece
        if (x > 0 && y < 7 && game.arr[x - 1][y + 1] < 0) {
            int temp[5] = {x, y, x - 1, y + 1, scorearr[game.arr[x - 1][y + 1] + 6]};
            memcpy(moves[cur++], temp, 5*sizeof(int));
        }
        //piece forward and to the left. Same tests.
        if (x < 7 && y < 7 && game.arr[x + 1][y + 1] < 0) {
            int temp[5] = {x, y, x + 1, y + 1, scorearr[game.arr[x + 1][y + 1] + 6]};
            memcpy(moves[cur++], temp, 5 * sizeof(int));
        }
        //piece forward one square. Tests if square exists and is empty. 
        if (y < 7 && game.arr[x][y + 1] == 0) {
            int temp[5] = {x, y, x, y + 1, 0};
            memcpy(moves[cur++], temp, 5 * sizeof(int));
            //can only move forward two peices if you can move forward one piece and started from original position
            if (y == 1 && game.arr[x][y + 2] == 0) {
                int temp[5] = {x,y,x,y+2,0};
                memcpy(moves[cur++], temp, 5 * sizeof(int));
            }
        }
    }
    else if (side == -1)
    {
        //piece forward and to the left. Tests if there is space to the right and forward of the pawn and if the space has an opposing piece
        if (x > 0 && y > 0 && game.arr[x - 1][y - 1] > 0)
        {
            int temp[5] = {x, y, x - 1, y - 1, scorearr[game.arr[x - 1][y + 1] + 6]};
            memcpy(moves[cur++], temp, 5 * sizeof(int));
        }
        //piece forward and to the left. Same tests.
        if (x < 7 && y > 0 && game.arr[x + 1][y - 1] > 0)
        {
            int temp[5] = {x, y, x + 1, y - 1, scorearr[game.arr[x + 1][y + 1] + 6]};
            memcpy(moves[cur++], temp, 5 * sizeof(int));
        }
        //piece forward one square. Tests if square exists and is empty.
        if (y > 0 && game.arr[x][y - 1] == 0)
        {
            int temp[5] = {x, y, x, y - 1, 0};
            memcpy(moves[cur++], temp, 5 * sizeof(int));
            //can only move forward two peices if you can move forward one piece and started from original position
            if (y == 6 && game.arr[x][y + 2] == 0)
            {
                int temp[5] = {x, y, x, y - 2, 0};
                memcpy(moves[cur++], temp, 5 * sizeof(int));
            }
        }
    }
    else {
        printf("Problem\n");
    }
    return cur;
}