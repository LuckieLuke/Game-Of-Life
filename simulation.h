#ifndef SIMULATION_H
#define SIMULATION_H

typedef struct b
{
    int height, width;
    int **life, **copy;
} * board;

void printBoard(board b);
board generate(board b, int n, int sbs, char *output);
void copy(board b);
void delete (board b);
int isDifferent(board b);

#endif
