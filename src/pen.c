#include <pen.h>

#include <toolbar.h>
#include <sheet.h>
#include <colors.h>

void pen_init(void *tb) {

}

void pen_event(void *tb) {
    chtype ch;
    ToolBar *toolbar = (ToolBar *) tb;
    Sheet *sheet = toolbar->instance;
    
    switch (toolbar->key) {
        case 'd':
            sheet->current_ch_x ++;
            if (sheet->current_ch_x >= 13) sheet->current_ch_x = 1;
            break;
        case 's':
            sheet->current_ch_y ++;
            if (sheet->current_ch_y >= 17) sheet->current_ch_y = 1;
            break;
        case 'a':
            sheet->current_ch_x --;
            if (sheet->current_ch_x <= 0) sheet->current_ch_x = 12;
            break;
        case 'w':
            sheet->current_ch_y --;
            if (sheet->current_ch_y <= 0) sheet->current_ch_y = 16;
            break;
    }

    ch = mvwinch(toolbar->wnd,
                    sheet->current_ch_y,
                    sheet->current_ch_x);

    sheet->current_char = 0xFF & ch;
    if (A_ALTCHARSET & ch)
        sheet->current_attr |= A_ALTCHARSET;
    else
        sheet->current_attr &= ~A_ALTCHARSET;
}

void pen_draw(void *tb) {
    int i, y = 1, x = 1;
    ToolBar *toolbar = (ToolBar *) tb;
    Sheet *sheet = (Sheet *) toolbar->instance;

    for (i = 32; i < 128; i ++) {

        if (i == sheet->current_char && !(sheet->current_attr & A_ALTCHARSET))
            wattron(toolbar->wnd, COLOR_PAIR(COLOR_PEN_SEL));

        if (i != 127)
            mvwaddch(toolbar->wnd, y, x, i);

        if (i == sheet->current_char && !(sheet->current_attr & A_ALTCHARSET))
            wattroff(toolbar->wnd, COLOR_PAIR(COLOR_PEN_SEL));

        y ++;
        if (y >= 17) {
            y = 1; x += 1;
        }
    }

    wattron(toolbar->wnd, A_ALTCHARSET);
    for (i = 32; i < 128; i ++) {

        if (i == sheet->current_char && (sheet->current_attr & A_ALTCHARSET))
            wattron(toolbar->wnd, COLOR_PAIR(COLOR_PEN_SEL));

        if (i != 127)
            mvwaddch(toolbar->wnd, y, x, i);

        if (i == sheet->current_char && (sheet->current_attr & A_ALTCHARSET))
            wattroff(toolbar->wnd, COLOR_PAIR(COLOR_PEN_SEL));

        y ++;
        if (y >= 17) {
            y = 1; x += 1;
        }
    }
    wattroff(toolbar->wnd, A_ALTCHARSET);

}

void pen_clean(void *tb) {
    
}