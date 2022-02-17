#include <sheet.h>
#include <stdlib.h>

#include <colors.h>

void cell_draw(Cell *cell, int x, int y);

void sheet_init(Sheet *sheet) {
    sheet->data = (Cell *) calloc(sheet->width * sheet->height, sizeof(Cell));
    sheet->cursor = 0;
}

void sheet_draw(Sheet *sheet) {
    int i, j, index;
    Cell *cell;

    for (j = 0; j < sheet->height; j ++) {
        for (i = 0; i < sheet->width; i ++) {

            index = j * sheet->width + i;
            cell = &sheet->data[index];

            if (index == sheet->cursor) attron(A_REVERSE);

            if (cell->active)
                cell_draw(cell, i + sheet->x, j + sheet->y);
            else {
                /* Draw background */
                attron(COLOR_PAIR(COLOR_SHEET_BG) | A_ALTCHARSET);
                mvaddch(j + sheet->y, i + sheet->x, /*ACS_CKBOARD*/ ' ');
                attroff(COLOR_PAIR(COLOR_SHEET_BG) | A_ALTCHARSET);
            }

            if (index == sheet->cursor) attroff(A_REVERSE);
        }
    }
}

void cell_draw(Cell *cell, int x, int y) {
    attron(cell->attr);
    mvaddch(y, x, cell->ch);
    attroff(cell->attr);
}

void sheet_print_ch(Sheet *sheet) {
    sheet->data[sheet->cursor].ch = sheet->current_char;
    sheet->data[sheet->cursor].attr = sheet->current_attr;
    sheet->data[sheet->cursor].active = 1;
}

void sheet_center(Sheet *sheet) {
    int w, h;
    getmaxyx(stdscr, h, w);

    sheet->x = w / 2 - sheet->width / 2;
    sheet->y = h / 2 - sheet->height / 2;
}
