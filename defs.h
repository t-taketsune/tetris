#ifndef DEFS_H
#define DEFS_H

#define EMPTY 0
#define PIECE_SIZE 4
#define N_PIECES 7

typedef struct {
    int i, j;
} coor;

typedef struct {
    coor real[PIECE_SIZE], inner[PIECE_SIZE];
    short int swtch;
} piece;

typedef struct {
    short int **field, piece_queue[7];
    int i_max, j_max, loop, collision;
    piece c;
} game;

#endif
