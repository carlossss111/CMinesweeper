#include "mouse.h"
#include <ncurses.h>

void init_mouse(){
    mousemask(BUTTON1_CLICKED, NULL);
    keypad(stdscr, TRUE);
    return;
}

void get_mouse(Vec* vec){
    int c = getch();
    MEVENT event;

    // Populate vector with raw position
    if (c == KEY_MOUSE){
        if (getmouse(&event) == OK) {
            char msg[64];
            sprintf(msg, "Mouse clicked: %d %d", event.x, event.y);
            log(Debug, msg);

            vec->y = event.x;
            vec->x = event.y;
        }
    }
}
