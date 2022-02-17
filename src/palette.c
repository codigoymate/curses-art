#include <palette.h>

#include <ncurses.h>
#include <toolbar.h>
#include <sheet.h>

void palette_init(void *tb) {
    int bg, fg, p = 1;

    for (bg = 0; bg < 8; bg ++)
        for (fg = 0; fg < 8; fg ++) {
            init_pair(p, fg, bg); p ++;
        }
}

void palette_event(void *tb) {
    chtype ch;
    ToolBar *toolbar = (ToolBar *) tb;
    Sheet *sheet = (Sheet *) toolbar->instance;

    switch (toolbar->key) {
    case KEY_UP:
        sheet->current_col_y --;
        if (sheet->current_col_y <= 0) sheet->current_col_y = 8;
        break;
    case KEY_DOWN:
        sheet->current_col_y ++;
        if (sheet->current_col_y > 8) sheet->current_col_y = 1;
        break;
    case KEY_LEFT:
        sheet->current_col_x --;
        if (sheet->current_col_x <= 0) sheet->current_col_x = 24;
        break;
    case KEY_RIGHT:
        sheet->current_col_x ++;
        if (sheet->current_col_x > 24) sheet->current_col_x = 1;
        break;
    }

    ch = mvwinch(toolbar->wnd, sheet->current_col_y, sheet->current_col_x);

    sheet->current_attr &= ~A_COLOR;
    sheet->current_attr |= ch & A_COLOR;

    if (ch & A_BOLD) {
        sheet->current_attr |= A_BOLD;
    } else {
        sheet->current_attr &= ~A_BOLD;
    }

    if (ch & A_DIM) {
        sheet->current_attr |= A_DIM;
    } else {
        sheet->current_attr &= ~A_DIM;
    }
}

void palette_draw(void *tb) {
    int i = 1, x = 1, y = 1;
    ToolBar *toolbar = (ToolBar *) tb;
    Sheet *sheet = (Sheet *) toolbar->instance;

    if (sheet->current_attr & A_ALTCHARSET)
        wattron(toolbar->wnd, A_ALTCHARSET);

    for (i = 1; i <= 64; i ++) {
        wattron(toolbar->wnd, COLOR_PAIR(i) | A_DIM);
        mvwaddch(toolbar->wnd, y, x, sheet->current_char);
        wattroff(toolbar->wnd, COLOR_PAIR(i) | A_DIM);
        y ++;
        if (y >= 9) {
            y = 1; x ++;
        }
    }

    y = 1;

    for (i = 1; i <= 64; i ++) {
        wattron(toolbar->wnd, COLOR_PAIR(i));
        mvwaddch(toolbar->wnd, y, x, sheet->current_char);
        wattroff(toolbar->wnd, COLOR_PAIR(i));
        y ++;
        if (y >= 9) {
            y = 1; x ++;
        }
    }

    y = 1;

    for (i = 1; i <= 64; i ++) {
        wattron(toolbar->wnd, COLOR_PAIR(i) | A_BOLD);
        mvwaddch(toolbar->wnd, y, x, sheet->current_char);
        wattroff(toolbar->wnd, COLOR_PAIR(i) | A_BOLD);
        y ++;
        if (y >= 9) {
            y = 1; x ++;
        }
    }

    if (sheet->current_attr & A_ALTCHARSET)
        wattroff(toolbar->wnd, A_ALTCHARSET);

    /* Draw color cursors */
    wattron(toolbar->wnd, A_ALTCHARSET);
    mvwaddch(toolbar->wnd, sheet->current_col_y, 25, ACS_LARROW);
    mvwaddch(toolbar->wnd, 9, sheet->current_col_x, ACS_UARROW);
    wattroff(toolbar->wnd, A_ALTCHARSET);
}

void palette_clean(void *tb) {

}
