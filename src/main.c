#include <ncurses.h>
#include <curses_art.h>
#include <parser.h>
#include <colors.h>
#include <toolbar.h>
#include <pen.h>
#include <palette.h>
#include <statusbar.h>
#include <titlebar.h>
#include <file_utils.h>
#include <code_gen.h>

int main(int argc, char *argv[]) {

    int key = 0, w, h;

    CursesArt *art = curses_art_new();
    ToolBar *pen = NULL, *palette = NULL;

    if (!parse_arguments(art, argc, argv)) {
        curses_art_destroy(art);
        return 1;
    }

    /* Try to load file */
    load_file(art);

    /* Start ncurses */
    initscr();
    getmaxyx(stdscr, h, w);
    start_color();
    init_pairs();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    /* Center sheet */
    sheet_center(&art->sheet);

    /* Pen toolbar */
    pen = toolbar_new(0, 3, 14, 18,
        pen_init, pen_event, pen_draw, pen_clean);
    pen->instance = &art->sheet;

    /* Palette toolbar */
    palette = toolbar_new(w - 27, 3, 27, 11,
        palette_init, palette_event, palette_draw, palette_clean);
    palette->instance = &art->sheet;

    while (key != 'q' && key != 'Q') {

        clear();

        sheet_draw(&art->sheet);

        titlebar_draw(art);
        statusbar_draw(art);

        refresh();

        toolbar_draw(pen);
        toolbar_draw(palette);

        key = getch();

        switch(key) {
        case KEY_RESIZE:
            sheet_center(&art->sheet);
            getmaxyx(stdscr, h, w);
            (void) h;
            mvwin(palette->wnd, w - 27, 3);
            wrefresh(palette->wnd);
            break;
        case 'i' & 0x1F: art->sheet.y --; break;
        case 'k' & 0x1F: art->sheet.y ++; break;
        case 'j' & 0x1F: art->sheet.x --; break;
        case 'l' & 0x1F: art->sheet.x ++; break;

        case 'i':
            art->sheet.cursor -= art->sheet.width;
            if (art->sheet.cursor < 0) art->sheet.cursor += art->sheet.width;
            break;

        case 'k':
            art->sheet.cursor += art->sheet.width;
            if (art->sheet.cursor >= art->sheet.width * art->sheet.height)
                art->sheet.cursor -= art->sheet.width;
            break;

        case 'l':
            art->sheet.cursor ++;
            if (art->sheet.cursor >= art->sheet.width * art->sheet.height)
                art->sheet.cursor = 0;
            break;

        case 'j':
            art->sheet.cursor --;
            if (art->sheet.cursor < 0)
                art->sheet.cursor = art->sheet.width * art->sheet.height - 1;
            break;

        case ' ':
            sheet_print_ch(&art->sheet);
            break;

        case 'w':
        case 'W':
        case 'a':
        case 'A':
        case 's':
        case 'S':
        case 'd':
        case 'D':
            toolbar_event(pen, key);
            break;

        /* Center Sheet */
        case 'c':
        case 'C':
            sheet_center(&art->sheet);
            break;

        /* Show / hide sheet bg */
        case 'v':
        case 'V':
            if (art->sheet.bg) art->sheet.bg = 0;
            else art->sheet.bg = 1;
    
        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
            toolbar_event(palette, key);
            break;

        case KEY_F(2):
            save_file(art);
            generate_source(art);
            break;
        }

    }

    toolbar_clean(pen);
    toolbar_clean(palette);

    endwin();
    curses_art_destroy(art);

    return 0;
}

