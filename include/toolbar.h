#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <ncurses.h>

typedef void (*FUNC_PTR)(void *);

typedef struct {
    WINDOW *wnd;
    void *instance;
    void (* event)(void *);
    void (* draw)(void *);
    void (* clean)(void *);
    int key;
} ToolBar;

ToolBar *toolbar_new(int x, int y, int w, int h,
        FUNC_PTR init, FUNC_PTR event, FUNC_PTR draw, FUNC_PTR clean);

void toolbar_clean(ToolBar *tb);
void toolbar_event(ToolBar *tb, int key);
void toolbar_draw(ToolBar *tb);

#endif
