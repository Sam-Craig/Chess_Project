#ifndef CHESS_COMM_H

#define CHESS_COMM_H

// Package for handling creation and running of games

typedef struct{
    int inputfiledes;
    int outputfiledes;
    int color;
    char name[];
} manual_player;

typedef struct{
    int pid;
    int color;
} cpu_player;

// Game is created -> 
// while not checkmated white inputs move -> black given move -> black inputs move -> white sees 

#endif