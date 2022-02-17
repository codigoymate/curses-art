#ifndef CURSES_ART_H
#define CURSES_ART_H

#include <sheet.h>

typedef struct {
    char *filename;
    Sheet sheet;
} CursesArt;

CursesArt *curses_art_new(void);
void curses_art_destroy(CursesArt *);

#endif