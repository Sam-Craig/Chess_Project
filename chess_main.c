#include "chess_main.h"
#include "chess_util.h"
#include <stdio.h>

int main(void)
{
    board *newboard = initboard();
    printboard(*newboard);
    printf("executing move\n");
    movepiece(newboard, 2,1,2,3,0);
    printboard(*newboard);
    return (0);
}