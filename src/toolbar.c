#include <toolbar.h>

#include <stdlib.h>

ToolBar *toolbar_new(int x, int y, int w, int h,
        FUNC_PTR init, FUNC_PTR event, FUNC_PTR draw, FUNC_PTR clean) {
    ToolBar *tb = (ToolBar *) malloc(sizeof(ToolBar));

    tb->wnd = newwin(h, w, y, x);
    tb->event = event;
    tb->draw = draw;
    tb->clean = clean;

    init(tb);

    return tb;
}

void toolbar_clean(ToolBar *tb) {
    tb->clean(tb);
    delwin(tb->wnd);
    free(tb);
}

void toolbar_event(ToolBar *tb, int key) {
    tb->key = key;
    tb->event(tb);
}

void toolbar_draw(ToolBar *tb) {
    wclear(tb->wnd);
    box(tb->wnd, 0, 0);
    tb->draw(tb);

    wrefresh(tb->wnd);
}
