#include "chess_main.h"
#include "chess_util.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    board *newboard = initboard();
    printboard(*newboard);
    pmoves *p1 = getlegalmoves(*newboard, 1);
    printpossiblemoves(p1, *newboard);
    free(p1);
    movepiece(newboard, 0, 6, 0, 2, 0);
    printboard(*newboard);
    pmoves *p2 = getlegalmoves(*newboard, 1);
    printpossiblemoves(p2, *newboard);
    free(p2);
    return (0);
}