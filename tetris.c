#include <ncurses.h>
#include <unistd.h>
#include "moving.h"
#include "init.h"

int main() {
    game g;
    int aux;
    init_game(&g);
    for (aux=0; aux!=20; aux++) {
        draw_game(stdscr, &g);
        move_piece(stdscr, &g);
    }
    endwin();
    return 0;
}
