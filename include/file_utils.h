#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <curses_art.h>

/**
 * @brief Write the current draw in the file.
 * The filename is art->filename.
 * 
 * First write the draw dimension:
 * (int) width
 * (int) height
 * 
 * Second write the draw data:
 * (chtype) data[w * h]
 * 
 * @param art Curses art instance.
 */
void save_file(CursesArt *art);

/**
 * @brief Load the draw form the file especified in art->filename.
 * 
 * @param art Curses art instance.
 */
void load_file(CursesArt *art);

#endif