#include <ncurses.h>
#include "init.h"
#include "moving.h"

int main() {
    game g;
    init_game(&g);
    wgetch(stdscr);

    endwin();
    return 1;
}
