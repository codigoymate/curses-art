#include <titlebar.h>

#include <ncurses.h>
#include <colors.h>
#include <string.h>

void titlebar_draw(CursesArt *art) {

    int w, h, i;
    (void) h;
    getmaxyx(stdscr, h, w);

    attron(COLOR_PAIR(COLOR_TITLE) | A_BOLD);

    for (i = 0; i < w; i ++)
        mvaddch(0, i, ' ');

    move(0, w / 2 - (strlen(art->filename) + 13) / 2);
    printw("Curses Art [%s]", art->filename);

    attroff(COLOR_PAIR(COLOR_TITLE) | A_BOLD);
}