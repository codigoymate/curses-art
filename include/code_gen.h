#ifndef CODE_GEN_H
#define CODE_GEN_H

#include <curses_art.h>

/**
 * @brief Generates source code that is capable of being executed to display the drawing
 * 
 * @param art Curses art instance.
 */
void generate_source(CursesArt *art);

#endif
