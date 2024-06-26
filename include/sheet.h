#ifndef SHEET_H
#define SHEET_H

#include <ncurses.h>

typedef struct {
    int attr, ch, active;
} Cell;

typedef struct {
    int width, height;
    int x, y;
    Cell *data;
    int cursor;
    chtype current_char, current_attr;
    int current_ch_x, current_ch_y;
    int current_col_x, current_col_y;
    int bg, modified, mouse_mode;
} Sheet;

void sheet_init(Sheet *sheet);
void sheet_draw(Sheet *sheet);

void sheet_print_ch(Sheet *sheet);
void sheet_delete_ch(Sheet *sheet);

void sheet_center(Sheet *sheet);
void sheet_resize(Sheet *sheet, int w, int h);

void sheet_shift_h(Sheet *sheet, int dir);
void sheet_shift_v(Sheet *sheet, int dir);

#endif
