#include "chess_main.h"
#include "chess_util.h"
#include <stdio.h>

int main(void)
{
    board *newboard = initboard();
    printboard(*newboard);
    pmoves * p1 = getlegalmoves(*newboard, 1);
    printpossiblemoves(p);
    free(p1);
    return (0);
}