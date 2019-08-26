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

void printpossiblemoves(pmoves * possiblemoves, board game) 
{
    printf("# of possible moves%d\n", possiblemoves -> cur);
    for (int i = 0; i < possiblemoves -> cur; i++) 
    {
        int ox = (possiblemoves->movearr)[i][0];
        int oy = (possiblemoves->movearr)[i][1];
        int dx = (possiblemoves->movearr)[i][2];
        int dy = (possiblemoves->movearr)[i][3];
        char opiece = inttopiece(game.arr[ox][oy]);
        char dpiece = inttopiece(game.arr[dx][dy]);
        //todo, make this something better, possibly a proper chess notation
        printf("%d %c:(%d, %d) -> (%d, %d)x%c\n", i, opiece, ox, oy, dx, dy, dpiece);
    }
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


//ToDo: Make testlegal work
void movepiece(board *game, int xinit, int yinit, int xdest, int ydest, int testlegal) {
    int piece = game->arr[yinit][xinit];
    game->arr[ydest][xdest] = piece;
    game->arr[yinit][xinit] = 0;
}

//gets all legal moves for a side with given board. Stores it in a 2d array of the form [[piecexloc, pieceyloc, destxloc, destyloc, points]...] with space for all possible moves 32 moves for pawns, 28 moves for rooks, 16 moves for knights, 28 moves for bishops, 28 moves for queen, 8 moves for king = 140 possible moves. Hence movearr is a 140x5 array. 

//side:1 = white, -1 = black

pmoves * getlegalmoves(board game, int side)
{
    // Remember to free after done using
    pmoves * possiblemoves = malloc(sizeof(pmoves));
    possiblemoves -> cur = 0;
    //Variable to keep track of pieces visited. Once we visit 16 pieces, we can return.
    int cur = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (cur == 16) return possiblemoves;
            //if the tile contains a pawn of the correct side
            if (game.arr[i][j] == side * W_PAWN) {
                cur++;
                pawnlegalmoves(game, possiblemoves, i, j, side);
            }
            else if (game.arr[i][j] == side * W_KNIGHT)
            {
                cur++;
                knightlegalmoves(game, possiblemoves, i, j, side);
            }
            else if (game.arr[i][j] == side * W_BISHOP)
            {
                cur++;
                //bishoplegalmoves(game, possiblemoves, cur, i, j, side);
            }
            else if (game.arr[i][j] == side * W_ROOK)
            {
                cur++;
                // cur = rooklegalmoves(game, possiblemoves, cur, i, j, side);
            }
            else if (game.arr[i][j] == side * W_QUEEN)
            {
                cur++;
                // cur = queenlegalmoves(game, possiblemoves, cur, i, j, side);
            }
            else if (game.arr[i][j] == side * W_KING)
            {
                cur++;
                // cur = kinglegalmoves(game, possiblemoves, cur, i, j, side);
            }
        }
    }
    return possiblemoves;
}

// Returns a pointer to the first available moveinfoarr and increment cur
void insert_pmove(pmoves *moves, board game, int curx, int cury, int newx, int newy)
{
    moveinfoarr temp = {curx, cury, newx, newy, scorearr[game.arr[newx][newy] + 6]};
    memcpy((moves->movearr)[(moves->cur)++], temp, 5 * sizeof(int));
}

//ToDo: Add promotion, en passant, (possibly) combine sides
void pawnlegalmoves(board game, pmoves * moves, int x, int y, int side) 
{
    if (side == W) 
    {
        //piece forward and to the right. Tests if there is space to the right and forward of the pawn and if the space has an opposing piece
        if (y > 0 && x < 7 && game.arr[x + 1][y - 1] < 0)
            insert_pmove(moves, game, x, y, x + 1, y - 1);
        //piece forward and to the left. Same tests.
        if (x < 7 && y < 7 && game.arr[x + 1][y + 1] < 0)
            insert_pmove(moves, game, x, y, x + 1, y + 1);
        //piece forward one square. Tests if square exists and is empty. 
        if (x < 7 && game.arr[x+1][y] == 0) 
        {
            insert_pmove(moves, game, x, y, x + 1, y);
            if (x == 1 && game.arr[x+2][y] == 0)
                insert_pmove(moves, game, x, y, x + 2, y);                
        }
    }
    else if (side == B)
    {
        //piece forward and to the left. Tests if there is space to the right and forward of the pawn and if the space has an opposing piece
        if (x > 0 && y > 0 && game.arr[x - 1][y - 1] > 0)
            insert_pmove(moves, game, x, y, x - 1, y - 1);
        //piece forward and to the left. Same tests.
        if (y < 7 && x > 0 && game.arr[x - 1][y + 1] > 0)
            insert_pmove(moves, game, x, y, x - 1, y + 1);
        //piece forward one square. Tests if square exists and is empty.
        if (x > 0 && game.arr[x-1][y] == 0) 
        {
            //can only move forward two peices if you can move forward one piece and started from original position
            if (x == 6 && game.arr[x - 2][y] == 0)
                insert_pmove(moves, game, x, y, x - 2, y);
            else
                insert_pmove(moves, game, x, y, x - 1, y);
        }
    }
    else {
        printf("Side must be either 1 (white) or -1 (black)\n");
    }
}

void knightlegalmoves(board game, pmoves * moves, int x, int y, int side) 
{

    // 8 cases, starting forward right (from white's perspective) and going counter-clockwise
    // Forward, right (from white's perspective). We need x + 2 < 8 (=> x < 6), y - 1 >= 0 (=> y > 0), and new position is either empty or black
    if (x < 6 && y > 0 && (side * game.arr[x + 2][y - 1]) <= 0)
        insert_pmove(moves, game, x, y, x + 2, y - 1);
    // Forward, left
    if (x < 6 && y < 7 && (side * game.arr[x + 2][y + 1]) <= 0)
        insert_pmove(moves, game, x, y, x + 2, y + 1);
    // Left, forward
    if (x < 7 && y < 6 && (side * game.arr[x + 1][y + 2]) <= 0)
        insert_pmove(moves, game, x, y, x + 1, y + 2);
    // Left, backwards
    if (x > 0 && y < 6 && (side * game.arr[x - 1][y + 2]) <= 0)
        insert_pmove(moves, game, x, y, x - 1, y + 2);
    // Backwards, left
    if (x > 1 && y < 7 && (side * game.arr[x - 2][y + 1]) <= 0)
        insert_pmove(moves, game, x, y, x - 2, y + 1);
    // Backwards, right
    if (x > 1 && y > 0 && (side * game.arr[x - 2][y - 1]) <= 0)
        insert_pmove(moves, game, x, y, x - 2, y - 1);
    // Right, backwards
    if (x > 0 && y > 1 && (side * game.arr[x - 1][y - 2]) <= 0)
        insert_pmove(moves, game, x, y, x - 1, y - 2);
    // Right, forwards
    if (x < 7 && y > 1 && (side * game.arr[x + 1][y - 2]) <= 0)
        insert_pmove(moves, game, x, y, x + 1, y - 2);
}

void bishoplegalmoves(board game, pmoves * moves, int x, int y, int side) 
{
    // 4 cases (from white's perspective) forward right, forward left, backward left, backward right. Loop over each
    // forward right
    for (int i = 1; x + i < 8 && y - i >= 0 && side * game.arr[x + i][y - i] <= 0; i++)
        insert_pmove(moves, game, x, y, x + i, y - i);
    // forward left
    for (int i = 1; x + i < 8 && y + i <  8 && side * game.arr[x + i][y + i] <= 0; i++)
        insert_pmove(moves, game, x, y, x + i, y + i);
    // backward left
    for (int i = 1; x - i >= 0 && y + i < 8 && side * game.arr[x - i][y + i] <= 0; i++)
        insert_pmove(moves, game, x, y, x - i, y + i);
    // backward right
    for (int i = 1; x - i >= 0 && y - i < 8 && side * game.arr[x - i][y - i] <= 0; i++)
        insert_pmove(moves, game, x, y, x - i, y - i);
}

void rooklegalmoves(board game, pmoves * moves, int x, int y, int side) 
{
    // 4 cases (from white's perspective) forward, left, backward, right. Loop over each
    // forward
    for (int i = 1; x + i < 8 && side * game.arr[x + i][y] <= 0; i++)
        insert_pmove(moves, game, x, y, x + i, y);
    // left
    for (int i = 1; y + i <  8 && side * game.arr[x][y + i] <= 0; i++)
        insert_pmove(moves, game, x, y, x, y + i);
    // backward
    for (int i = 1; x - i >= 0 && side * game.arr[x - i][y] <= 0; i++)
        insert_pmove(moves, game, x, y, x - i, y);
    // right
    for (int i = 1; y - i < 8 && side * game.arr[x][y - i] <= 0; i++)
        insert_pmove(moves, game, x, y, x, y - i);
}

void queenlegalmoves(board game, pmoves * moves, int x, int y, int side) 
{
    // A queen is basically a rook and a bishop on the same square, right?
    bishoplegalmoves(game, moves, x, y, side);
    rooklegalmoves(game, moves, x, y, side);
}

// This is going to be very complicated b/c we need to test if any piece can move where the king wants to move to
void kinglegalmoves(board game, pmoves * moves, int x, int y, int side) 
{
    return;
}