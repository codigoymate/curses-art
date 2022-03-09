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
#include <quit_prompt.h>
#include <resize_mode.h>
#include <mouse.h>

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
    mousemask(BUTTON1_CLICKED | BUTTON3_CLICKED, NULL);

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

    while (!art->quit) {

        clear();

        sheet_draw(&art->sheet);

        titlebar_draw(art);
        statusbar_draw(art);

        if (art->quit_prompt) draw_quit_prompt();
        if (art->resize_mode) draw_resize_mode(art);

        refresh();

        toolbar_draw(pen);
        toolbar_draw(palette);

        if (art->quit_prompt) {
            update_quit_prompt(art);
            continue;
        }

        if (art->resize_mode) {
            update_resize_mode(art);
            continue;
        }

        key = getch();

        switch(key) {

        /* Termina resize */
        case KEY_RESIZE:
            sheet_center(&art->sheet);
            getmaxyx(stdscr, h, w);
            (void) h;
            mvwin(palette->wnd, w - 27, 3);
            wrefresh(palette->wnd);
            break;
        
        /* Mouse */
        case KEY_MOUSE:
            mouse_event(art);
            break;

        
        case 'i' & 0x1F: art->sheet.y --; break;
        case 'k' & 0x1F: art->sheet.y ++; break;
        case 'j' & 0x1F: art->sheet.x --; break;
        case 'l' & 0x1F: art->sheet.x ++; break;

        case 'i':
            art->sheet.cursor -= art->sheet.width;
            if (art->sheet.cursor < 0) art->sheet.cursor += art->sheet.width;
            art->sheet.mouse_mode = 0;
            break;

        case 'k':
            art->sheet.cursor += art->sheet.width;
            if (art->sheet.cursor >= art->sheet.width * art->sheet.height)
                art->sheet.cursor -= art->sheet.width;
            art->sheet.mouse_mode = 0;
            break;

        case 'l':
            art->sheet.cursor ++;
            if (art->sheet.cursor >= art->sheet.width * art->sheet.height)
                art->sheet.cursor = 0;
            art->sheet.mouse_mode = 0;
            break;

        case 'j':
            art->sheet.cursor --;
            if (art->sheet.cursor < 0)
                art->sheet.cursor = art->sheet.width * art->sheet.height - 1;
            art->sheet.mouse_mode = 0;
            break;

        case ' ':
            sheet_print_ch(&art->sheet);
            art->sheet.mouse_mode = 0;
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

        /* Resize Sheet */
        case 'r':
        case 'R':
            art->resize_mode = 1;
            art->neww = art->sheet.width;
            art->newh = art->sheet.height;
            break;

        /* Show / hide sheet bg */
        case 'v':
        case 'V':
            if (art->sheet.bg) art->sheet.bg = 0;
            else art->sheet.bg = 1;
    

        /* Move attr pallete cursor */
        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
            toolbar_event(palette, key);
            break;

        /* Save file */
        case KEY_F(2):
            save_file(art);
            generate_source(art);
            break;

        /* Delete character */
        case 'x':
        case 'X':
        case KEY_DC:
            sheet_delete_ch(&art->sheet);
            break;

         /* Quit */
        case 'q':
        case 'Q':
            curses_art_quit(art);
            break;
        }

    }

    toolbar_clean(pen);
    toolbar_clean(palette);

    endwin();
    curses_art_destroy(art);

    return 0;
}

