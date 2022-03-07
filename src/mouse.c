#include <mouse.h>

void button_left_click(CursesArt *art, int x, int y);
void button_right_click(CursesArt *art, int x, int y);

int inner_sheet(Sheet *sheet, int x, int y);

void mouse_event(CursesArt *art) {
    MEVENT event;

    if (getmouse(&event) == OK) {
        if (event.bstate == BUTTON1_CLICKED)
            button_left_click(art, event.x, event.y);
        if (event.bstate == BUTTON3_CLICKED) {
            button_right_click(art, event.x, event.y);
        }
    }
}

void button_left_click(CursesArt *art, int x, int y) {
    if (inner_sheet(&art->sheet, x, y)) {
        x -= art->sheet.x;
        y -= art->sheet.y;
        art->sheet.mouse_mode = 1;
        art->sheet.cursor = y * art->sheet.width + x;

        art->sheet.data[art->sheet.cursor].ch = art->sheet.current_char;
        art->sheet.data[art->sheet.cursor].attr = art->sheet.current_attr;
        art->sheet.data[art->sheet.cursor].active = 1;
        art->sheet.modified = 1;
    }
}

void button_right_click(CursesArt *art, int x, int y) {
    if (inner_sheet(&art->sheet, x, y)) {
        x -= art->sheet.x;
        y -= art->sheet.y;
        art->sheet.mouse_mode = 1;
        art->sheet.cursor = y * art->sheet.width + x;

        art->sheet.data[art->sheet.cursor].active = 0;
        art->sheet.modified = 1;
    }
}

int inner_sheet(Sheet *sheet, int x, int y) {
    int x1 = sheet->x;
    int y1 = sheet->y;
    int x2 = sheet->x + sheet->width;
    int y2 = sheet->y + sheet->height;

    return (x >= x1 && x < x2 && y >= y1 && y < y2);
}
