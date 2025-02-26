#include "input.h"
#include <ncurses.h>

void init_mouse(){
    mousemask(ALL_MOUSE_EVENTS, NULL);
    keypad(stdscr, TRUE);
    return;
}

void get_input(Vec* vec, bool* right_click, int* key){
    MEVENT event;
    int c = getch();
    *key = -1;

    // Populate vector with raw position
    if (c == KEY_MOUSE){
        if (getmouse(&event) == OK) {
            if (event.bstate & RIGHT_CLICKED){
                *right_click = true;
            }
            else{
                *right_click = false;
            }

            char msg[64];
            sprintf(msg, "Mouse clicked: %d %d", event.x, event.y);
            log(Debug, msg);

            vec->y = event.x;
            vec->x = event.y;
        }
    }

    // Else populate key pess
    else{
        *key = c;
    }
}
