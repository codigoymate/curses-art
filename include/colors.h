#ifndef COLORS_H
#define COLORS_H

#define COLOR_SHEET_BG      65
#define COLOR_PEN_SEL       66
#define COLOR_COLOR_SEL     67
#define COLOR_STATUS        68
#define COLOR_TITLE         69
#define COLOR_QUIT_PROMPT   70
#define COLOR_RESIZE_MODE   71

/**
 * @brief Init all ncurses color pairs.
 * 1 to 64 are reserved to draw palette.
 * 
 */
void init_pairs(void);

#endif
