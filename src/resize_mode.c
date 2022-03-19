#include <resize_mode.h>
#include <ctype.h>

#include <colors.h>
#include <sheet.h>

void draw_resize_mode(CursesArt *art) {

    int w, h, i;
    getmaxyx(stdscr, h, w);

    attron(COLOR_PAIR(COLOR_RESIZE_MODE));

    for (i = 0; i < w; i ++) {
        mvaddch(h - 3, i, ' ');
        mvaddch(h - 4, i, ' ');
    }

    mvprintw(h - 4, 5, "Previous size: (%i, %i); new size: (%i, %i).",
        art->sheet.width, art->sheet.height, art->neww, art->newh);

    mvprintw(h - 3, 5, "I, J, K, L: Change size; ENTER: Accept; ESC: Cancel.");

    attroff(COLOR_PAIR(COLOR_RESIZE_MODE));
}

void update_resize_mode(CursesArt *art) {

    int key;

    set_escdelay(0);

    key = toupper(getch());

    switch (key) {
    case 'I':
        art->newh --; if (art->newh < 1) art->newh = 1;
        break;
    case 'K':
        art->newh ++;
        break;
    case 'J':
        art->neww --; if (art->neww < 1) art->neww = 1;
        break;
    case 'L':
        art->neww ++;
        break;

    case 27:
        /* Cancel */
        art->resize_mode = 0;
        break;

    case 10:
        /* Accept */
        art->resize_mode = 0;
        sheet_resize(&art->sheet, art->neww, art->newh);
        break;
    }

}
