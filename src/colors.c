#include <colors.h>

#include <ncurses.h>

void init_pairs(void) {
    init_pair(COLOR_SHEET_BG, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_PEN_SEL, COLOR_WHITE, COLOR_GREEN);
    init_pair(COLOR_COLOR_SEL, COLOR_BLACK, COLOR_GREEN);
    init_pair(COLOR_STATUS, COLOR_WHITE, COLOR_GREEN);
    init_pair(COLOR_TITLE, COLOR_WHITE, COLOR_GREEN);
}
