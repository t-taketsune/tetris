#include <ncurses.h>
#include <stdlib.h>
#include "moving.h"

/* Utility function to draw the game. */
void draw_game(WINDOW * w, game * g) {
    int i, j;
    werase(w);
    for (i=0; i!=g->i_max; i++)
        for (j=0; j!=g->j_max; j++) {
            wattron(w, COLOR_PAIR(g->field[i][j]));
            mvwaddch(w, i, j, ' ');
            wattroff(w, COLOR_PAIR(g->field[i][j]));
        }
    wattron(w, COLOR_PAIR(g->c.swtch));
    for (i=0; i!=PIECE_SIZE; i++)
        mvwaddch(w, g->c.real[i].i, g->c.real[i].j, ' ');
    wattroff(w, COLOR_PAIR(g->c.swtch));
    wrefresh(w);
}

/* Utility function to roll a piece. */
static int roll(game * g) {
    coor delta[PIECE_SIZE], rolled[PIECE_SIZE];
    int i;

    for (i=0; i!=PIECE_SIZE; i++) {
        delta[i].j = g->c.inner[i].i;
        delta[i].i = - g->c.inner[i].j;
        rolled[i].i = g->c.real[i].i - delta[i].j - g->c.inner[i].j - ((g->c.inner[i].i >> 31) != (delta[i].i >> 31));
        rolled[i].j = g->c.real[i].j + delta[i].j - g->c.inner[i].j - ((g->c.inner[i].j >> 31) != (delta[i].j >> 31));

        if (rolled[i].i <= 0 || rolled[i].i >= g->i_max - 1 || g->field[rolled[i].i][rolled[i].j] != EMPTY)
            return 0;
    }

    for (i=0; i!=PIECE_SIZE; i++) {
        g->c.inner[i].i = delta[i].i;
        g->c.inner[i].j = delta[i].j;
        g->c.real[i].i = rolled[i].i;
        g->c.real[i].j = rolled[i].j;
    }
    return 1;
}

static int move_left(game * g) {
    int i;
    for (i=0; i!=PIECE_SIZE; i++)
        if (g->c.real[i].j == 0 || g->field[g->c.real[i].i][g->c.real[i].j - 1] != EMPTY)
            return 0;
    for (i=0; i!=PIECE_SIZE; i++)
        g->c.real[i].j--;
    return 1;
}

static int move_right(game * g) {
    int i;
    for (i=0; i!=PIECE_SIZE; i++)
        if (g->c.real[i].j == g->j_max - 1 || g->field[g->c.real[i].i][g->c.real[i].j + 1] != EMPTY)
            return 0;
    for (i=0; i!=PIECE_SIZE; i++)
        g->c.real[i].j++;
    return 1;
}

static int move_down(game * g) {
    int i;
    for (i=0; i!=PIECE_SIZE; i++)
        if (g->c.real[i].i == g->i_max - 1 || g->field[g->c.real[i].i][g->c.real[i].i + 1] != EMPTY)
            return 0;
    for (i=0; i!=PIECE_SIZE; i++)
        g->c.real[i].i++;
    return 1;
}

void move_piece(WINDOW * w, game * g) {
    switch (wgetch(w)) {
        case 'd': move_right(g); break;
        case 'a': move_left(g); break;
        case 's': move_down(g); break;
        case 'r': roll(g); break;
    }
}
