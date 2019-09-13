#include "chess_main.h"
#include "chess_util.h"
#include "chess_cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Parse command line inputs. I think this should be ./Main 
int main(int argc, char *argv[])
{
    int opt;
    FILE *fp;
    char inputfilename[] = "\"";
    //printf("%d", STDIN_FILENO);
    while ((opt = getopt(argc, argv, "if:t")) != -1) {
        switch (opt) {
        case 'i': 
            interactive(STDIN_FILENO); 
            break;
        case 'f': 
            fp = fopen(optarg, "r");
            if (fp == NULL) {
                fprintf(stderr, "Failed to read the file.\n");
                exit(EXIT_FAILURE);
            }
            interactive(fileno(fp));
            break;
        case 't': 
            code_test(); 
            break;
        default:
            fprintf(stderr, "Usage: %s [-ilw] [file...]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
}


int interactive(int filedes) {
    printf("%d\n", filedes);
    return 0;
}


int code_test(void) {
    // ad hoc testing for now; making, modifying, and printing boards + printing possible moves
    board *newboard = initboard();
    printboard(*newboard);
    pmoves *p1 = getlegalmoves(*newboard, 1);
    printpossiblemoves(p1, *newboard);
    movepiece(newboard, 0, 6, 0, 2, 0);
    printboard(*newboard);
    pmoves *p2 = getlegalmoves(*newboard, 1);
    printpossiblemoves(p2, *newboard);
    free(p1);
    free(p2);
    return (0);
}

