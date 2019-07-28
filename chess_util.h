#ifndef CHESS_UTIL_H

#define CHESS_UTIL_H

#define BOARD_WIDTH
#define BOARD_HEIGHT

#define MOVE_ARR_SIZE 140
#define MOVE_INFO_ARR_SIZE 5

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

// This is a 140x5 array.
typedef int moveinfoarr[MOVE_INFO_ARR_SIZE];

typedef struct{
    moveinfoarr movearr[MOVE_ARR_SIZE];
    int cur;
} pmoves;

// Could maybe be a macro?
char inttopiece(int piece);

void printpossiblemoves(pmoves *possiblemoves, board game);

void printboard(board toprint);

board* initboard();

void movepiece(board *game, int xinit, int yinit, int xdest, int ydest, int testlegal);

void insert_pmove(pmoves *moves, board game, int curx, int cury, int newx, int newy);

pmoves* getlegalmoves(board game, int side);

void pawnlegalmoves(board game, pmoves * moves, int x, int y, int side);

void knightlegalmoves(board game, pmoves * moves, int x, int y, int side);

void bishoplegalmoves(board game, pmoves * moves, int x, int y, int side);

void rooklegalmoves(board game, pmoves * moves, int x, int y, int side);

void queenlegalmoves(board game, pmoves * moves, int x, int y, int side);

// int kinglegalmoves(board game, movearr * moves, int cur, int x, int y, int side);

#endif