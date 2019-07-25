#ifndef CHESS_UTIL_H

#define CHESS_UTIL_H

typedef struct{
    //0 is empty square, 1 is white pawn, 2 is white knight, 3 is white bishop, 4 is white rook, 5 is white queen, 6 is white king
    //-1 is black paw, -2 is black knight, -3 is black bishop, -4 is black rook, -5 is black queen, -6 is black king
    //When pringing, upper case is white, lower case is black, n is knight
    //arr[0][0] is A1 to arr[8][8] is H8
    int arr[8][8];
} board;

// This is a 140x5 array. 
typedef int ** movearr;

char inttopiece(int piece);

void printboard(board toprint);

board* initboard();

void movepiece(board *game, int xinit, int yinit, int xdest, int ydest, int testlegal);

movearr getlegalmoves(board game, int side);

int pawnlegalmoves(board game, movearr moves, int cur, int x, int y, int side);

// int knightlegalmoves(board game, movearr * moves, int cur, int x, int y, int side);

// int bishoplegalmoves(board game, movearr * moves, int cur, int x, int y, int side);

// int rooklegalmoves(board game, movearr * moves, int cur, int x, int y, int side);

// int queenlegalmoves(board game, movearr * moves, int cur, int x, int y, int side);

// int kinglegalmoves(board game, movearr * moves, int cur, int x, int y, int side);

#endif