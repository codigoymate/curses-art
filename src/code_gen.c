#include <code_gen.h>
#include <stdio.h>
#include <ncurses.h>
#include <file_utils.h>
#include <string.h>

void generate_source(CursesArt *art) {
    int col = 0, i;
    chtype ch;
    char path[256];
    FILE *file;
    Sheet *sheet = &art->sheet;

    strcpy(path, art->filename);
    strcat(path, ".c");

    file = fopen(path, "w");

    fprintf(file, "#include <ncurses.h>\n\n");

    fprintf(file, "void draw(WINDOW *wnd);\n\n");

    fprintf(file, "int main(void) {\n");

    fprintf(file, "\tint bg, fg, p = 1;\n\n");

    fprintf(file, "    initscr();\n");
    fprintf(file, "    start_color();\n\n");

    fprintf(file, "    /* Init color pairs */\n");
    fprintf(file, "    for (bg = 0; bg < 8; bg ++) {\n");
    fprintf(file, "        for (fg = 0; fg < 8; fg ++) {\n");
    fprintf(file, "            init_pair(p, fg, bg); p ++;\n");
    fprintf(file, "        }\n");
    fprintf(file, "    }\n\n");

    fprintf(file, "    draw(stdscr);\n");
    fprintf(file, "    refresh();\n");
    fprintf(file, "    getch();\n");

    fprintf(file, "    endwin();\n\n");

    fprintf(file, "    return 0;\n");
    fprintf(file, "}\n\n");

    fprintf(file, "void draw(WINDOW *wnd) {\n");

    fprintf(file, "\tint w = %i, h = %i, x, y, i = 0;\n", sheet->width, sheet->height);

    fprintf(file, "\tchtype m[] = {\n");

    for (i = 0; i < sheet->width * sheet->height; i ++) {
        ch = 0;
        if (sheet->data[i].active) {
            ch |= sheet->data[i].ch & 0xFF;
            ch |= sheet->data[i].attr & ~0xFF;
        }
        fprintf(file, "%i", ch);
        if (i != sheet->width * sheet->height - 1)
            fprintf(file, ", ");
        col ++;
        if (col == 16) {
            col = 0;
            fprintf(file, "\n");
        }
    }

    fprintf(file, "\t};\n\n");

    fprintf(file, "\tfor (y = 0; y < h; y ++)\n");
    fprintf(file, "\t\tfor (x = 0; x < w; x ++) {\n");
    fprintf(file, "\t\t\tif (m[i]) mvwaddch(wnd, y, x, m[i]);\n");
    fprintf(file, "\t\t\ti ++;\n");
    fprintf(file, "\t\t}\n");

    fprintf(file, "}\n");

    fclose(file);
}
