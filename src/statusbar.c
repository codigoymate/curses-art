#include <statusbar.h>

#include <ncurses.h>
#include <colors.h>

void statusbar_draw(CursesArt *art) {
    int w, h, i;
    getmaxyx(stdscr, h, w);


    attron(COLOR_PAIR(COLOR_STATUS) | A_BOLD);

    for (i = 0; i < w; i ++)
        mvaddch(h - 1, i, ' ');

    move(h - 1, 0);
    printw(" Size: (%i, %i) |", art->sheet.width, art->sheet.height);
    printw(" Cursor: (%i, %i)", art->sheet.cursor % art->sheet.width,
                                art->sheet.cursor / art->sheet.width);
    printw(" Ch: %i%c", art->sheet.current_char, 
            art->sheet.current_attr & A_ALTCHARSET ? 'e' : ' ');

    attroff(COLOR_PAIR(COLOR_STATUS) | A_BOLD);
        
}
