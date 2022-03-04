#include <file_utils.h>
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

void save_file(CursesArt *art) {
    int i;
    chtype ch;
    FILE *file = fopen(art->filename, "wb");

    /* Write dimension */
    fwrite(&art->sheet.width, sizeof(int), 1, file);
    fwrite(&art->sheet.height, sizeof(int), 1, file);

    /* Write data */
    for (i = 0; i < art->sheet.width * art->sheet.height; i ++) {
        ch = 0;
        if (art->sheet.data[i].active) {
            ch = art->sheet.data[i].attr & ~0xFF;
            ch |= art->sheet.data[i].ch & 0xFF;
        }
        fwrite(&ch, sizeof(chtype), 1, file);
    }

    fclose(file);

    art->sheet.modified = 0;
}

void load_file(CursesArt *art) {
    FILE *file;
    int i;
    chtype ch;

    if (access(art->filename, F_OK) != 0) {
        /* File not exists */
        sheet_init(&art->sheet);
        return ;
    }

    file = fopen(art->filename, "rb");

    if (!file) {
        /* Reading error */
        sheet_init(&art->sheet);
        return ;
    }

    /* TODO: check file format */

    /* Open file ok */
    /* Read dimension */
    fread(&art->sheet.width, sizeof(int), 1, file);
    fread(&art->sheet.height, sizeof(int), 1, file);

    sheet_init(&art->sheet);

    for (i = 0; i < art->sheet.width * art->sheet.height; i ++) {
        fread(&ch, sizeof(chtype), 1, file);
        if (!ch) {
            art->sheet.data[i].active = 0;
            continue;
        }
        art->sheet.data[i].active = 1;
        art->sheet.data[i].ch = ch & 0xFF;
        art->sheet.data[i].attr = ch & ~0xFF;
    }


    fclose(file);
}

