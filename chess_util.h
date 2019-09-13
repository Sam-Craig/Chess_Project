#ifndef CHESS_UTIL_H

#define CHESS_UTIL_H

#define BOARD_WIDTH
#define BOARD_HEIGHT

// Macros for different pieces to improve clarity
#define BLANK 0

#define W 1
#define W_PAWN 1
#define W_KNIGHT 2
#define W_BISHOP 3
#define W_ROOK 4
#define W_QUEEN 5
#define W_KING 6

#define B -1
#define B_PAWN W_PAWN*B
#define B_KNIGHT W_KNIGHT*B
#define B_BISHOP W_BISHOP*B
#define B_ROOK W_ROOK*B
#define B_QUEEN W_QUEEN*B
#define B_KING W_KING*B

typedef struct{
    //0 is empty square, 1 is white pawn, 2 is white knight, 3 is white bishop, 4 is white rook, 5 is white queen, 6 is white king
    //-1 is black paw, -2 is black knight, -3 is black bishop, -4 is black rook, -5 is black queen, -6 is black king
    //When pringing, upper case is white, lower case is black, n is knight
    //arr[0][0] is A1 to arr[8][8] is H8
    int arr[8][8];
} board;

// Could maybe be a macro?
char inttopiece(int piece);


void printboard(board toprint);

board* initboard();

int movepiece(board * game, int xinit, int yinit, int xdest, int ydest, int test);

int testlegal(board * game, int xinit, int yinit, int xdest, int ydest);

extern const int scorearr[13];

int incheck(board game, int side);

int incheckmate(board game, int side);

#endif