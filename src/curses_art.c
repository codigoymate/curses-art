#include <curses_art.h>
#include <stdlib.h>

CursesArt *curses_art_new(void) {
    CursesArt *art = (CursesArt *) malloc(sizeof(CursesArt));
    art->filename = NULL;
    art->sheet.width = 40;
    art->sheet.height = 9;
    art->sheet.data = NULL;
    art->sheet.current_char = ' ';
    art->sheet.current_attr = 0;
    art->sheet.current_ch_x = art->sheet.current_ch_y = 1;
    art->sheet.current_col_x = 1;
    art->sheet.current_col_y = 8;

    return art;
}

void curses_art_destroy(CursesArt *art) {
    if (art->filename != NULL)
        free(art->filename);
    if (art->sheet.data != NULL)
        free(art->sheet.data);
    free(art);
}
