#include "init.h"
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

void shuffle(short int * queue) {
    int i, aux, target;
    for (i=0; i!=N_PIECES; i++)
        queue[i] = i + 1;
    for (i=0; i!=N_PIECES; i++) {
        target = rand()%N_PIECES;
        aux = queue[i];
        queue[i] = queue[target];
        queue[target] = aux;
    }
}

static void init_1(piece * p, int start) {
    int aux;
    /*  0000
        XXXX
        0000
        0000  */
    for (aux=0; aux!=4; aux++) {
        p->inner[aux].i = 1;
        p->real[aux].i = 1;
        p->real[aux].j = start - 2 + aux;
    }
    for (aux=-2; aux!=0; aux++)
        p->inner[aux].j = aux;
    for (aux=1; aux!=3; aux++)
        p->inner[aux].j = aux;
}

static void init_2(piece * p, int start) {
    /*  0000
        0XX0
        0XX0
        0000  */
    p->inner[0].i = 1;
    p->inner[0].j = -1;
    p->inner[1].i = 1;
    p->inner[1].j = 1;
    p->inner[2].i = -1;
    p->inner[2].j = 1;
    p->inner[3].i = -1;
    p->inner[3].j = -1;
    p->real[0].i = 1;
    p->real[0].j = start - 1;
    p->real[1].i = 1;
    p->real[1].j = start;
    p->real[2].i = 2;
    p->real[2].j = start - 1;
    p->real[3].i = 2;
    p->real[3].j = start;
}

static void init_3(piece * p, int start) {
    /*  00X0
        0XXX
        0000
        0000  */
    p->inner[0].i = 1;
    p->inner[0].j = -1;
    p->inner[1].i = 1;
    p->inner[1].j = 1;
    p->inner[2].i = 1;
    p->inner[2].j = 2;
    p->inner[3].i = 2;
    p->inner[3].j = 1;
    p->real[0].i = 2;
    p->real[0].j = start - 1;
    p->real[1].i = 2;
    p->real[1].j = start;
    p->real[2].i = 2;
    p->real[2].j = start + 1;
    p->real[3].i = 1;
    p->real[3].j = start;
}

static void init_4(piece * p, int start) {
    /*  0000
        0X00
        0XXX
        0000  */
    p->inner[0].i = 1;
    p->inner[0].j = -1;
    p->inner[1].i = -1;
    p->inner[1].j = -1;
    p->inner[2].i = -1;
    p->inner[2].j = 1;
    p->inner[3].i = -1;
    p->inner[3].j = 2;
    p->real[0].i = 1;
    p->real[0].j = start - 1;
    p->real[1].i = 2;
    p->real[1].j = start - 1;
    p->real[2].i = 2;
    p->real[2].j = start;
    p->real[3].i = 2;
    p->real[3].j = start + 1;
}

static void init_5(piece * p, int start) {
    /*  0000
        0XXX
        0X00
        0000  */
    p->inner[0].i = 1;
    p->inner[0].j = -1;
    p->inner[1].i = 1;
    p->inner[1].j = 1;
    p->inner[2].i = 1;
    p->inner[2].j = 2;
    p->inner[3].i = -1;
    p->inner[3].j = -1;
    p->real[0].i = 1;
    p->real[0].j = start - 1;
    p->real[1].i = 1;
    p->real[1].j = start;
    p->real[2].i = 1;
    p->real[2].j = start + 1;
    p->real[3].i = 2;
    p->real[3].j = start - 1;
}

static void init_6(piece * p, int start) {
    /*  0000
        00XX
        0XX0
        0000  */
    p->inner[0].i = 1;
    p->inner[0].j = 1;
    p->inner[1].i = 1;
    p->inner[1].j = 2;
    p->inner[2].i = -1;
    p->inner[2].j = -1;
    p->inner[3].i = -1;
    p->inner[3].j = 1;
    p->real[0].i = 1;
    p->real[0].j = start;
    p->real[1].i = 1;
    p->real[1].j = start + 1;
    p->real[2].i = 2;
    p->real[2].j = start;
    p->real[3].i = 2;
    p->real[3].j = start - 1;
}

static void init_7(piece * p, int start) {
    /*  0000
        0XX0
        00XX
        0000  */
    p->inner[0].i = 1;
    p->inner[0].j = -1;
    p->inner[1].i = 1;
    p->inner[1].j = 1;
    p->inner[2].i = -1;
    p->inner[2].j = 1;
    p->inner[3].i = -1;
    p->inner[3].j = 2;
    p->real[0].i = 1;
    p->real[0].j = start - 1;
    p->real[1].i = 1;
    p->real[1].j = start;
    p->real[2].i = 2;
    p->real[2].j = start;
    p->real[3].i = 2;
    p->real[3].j = start + 1;
}

void init_colors() {
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(4, COLOR_BLACK, COLOR_BLUE);
    init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(6, COLOR_BLACK, COLOR_CYAN);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
}

void init_piece(game * g) {
    switch (g->c.swtch) {
        case 1: init_1(&g->c, (g->j_max)/2); break;
        case 2: init_2(&g->c, (g->j_max)/2); break;
        case 3: init_3(&g->c, (g->j_max)/2); break;
        case 4: init_4(&g->c, (g->j_max)/2); break;
        case 5: init_5(&g->c, (g->j_max)/2); break;
        case 6: init_6(&g->c, (g->j_max)/2); break;
        case 7: init_7(&g->c, (g->j_max)/2); break;
    }
}

void update_current(game * g) {
    if (g->loop == N_PIECES) {
        shuffle(g->piece_queue);
        g->loop = 0;
    }
    g->loop+=1;
    g->c.swtch = g->piece_queue[0];
    int i;
    for (i=0; i!=N_PIECES - 1; i++) {
        g->piece_queue[i] = g->piece_queue[i+1];
    }
    init_piece(g);
}

int alloc_field(game * g) {
    int aux;
    g->field = malloc(sizeof(short int*)*g->i_max);
    if (!g->field)
        return 0;
    for (aux=0; aux!=g->i_max; aux++) {
        g->field[aux] = malloc(sizeof(short int)*g->j_max);
        if (!g->field[aux])
            return 0;
    }
    return 1;
}

void init_field(game * g) {
    int i, j;
    for (i=0; i!=g->i_max; i++)
        for (j=0; j!=g->j_max; j++)
            g->field[i][j] = EMPTY;
    for (i=0; i!=PIECE_SIZE; i++)
        g->field[g->c.real[i].i][g->c.real[i].j] = g->c.swtch;
}

void init_game(game * g) {
    initscr();
    init_colors();
    printw("Please provide the size for the grid. (rows, columns)");
    int w_i, w_j;
    while (TRUE) {
        scanw("%d %d", &g->i_max, &g->j_max);
        getmaxyx(stdscr, w_i, w_j);
        if (g->i_max <= w_i && g->j_max <= w_j)
            break;
        printw("Terminal is too small. Try again.");
    }
    if (!alloc_field(g)) {
        printw("Not enough memory. Shutting down.");
        endwin();
        exit(0);
    }
    srand(time(NULL));
    g->collision = 0;
    g->loop = 0;
    shuffle(g->piece_queue);
    update_current(g);
}
