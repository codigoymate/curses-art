#include <quit_prompt.h>

#include <ncurses.h>
#include <file_utils.h>
#include <code_gen.h>
#include <colors.h>

void draw_quit_prompt(void) {
    int w, h;
    getmaxyx(stdscr, h, w);

    move(h / 4 * 3, w / 2 - 21);
    attron(COLOR_PAIR(COLOR_QUIT_PROMPT));
    printw("   Save changes before exit ? (y/n/c)   ");
    attroff(COLOR_PAIR(COLOR_QUIT_PROMPT));

}

void update_quit_prompt(CursesArt *art) {
    int q = 0;

    noecho();

    while (!q) {
        switch (getch()) {
        case 'y':
        case 'Y':
            art->quit = 1;
            save_file(art);
            generate_source(art);
            q = 1;
            break;
        
        case 'n':
        case 'N':
            art->quit = 1;
            q = 1;
            break;

        case 'c':
        case 'C':
            art->quit_prompt = 0;
            q = 1;
            break;
        }
    }

}