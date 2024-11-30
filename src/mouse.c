#include "mouse.h"
#include <ncurses.h>

void mouse_init(){
    mousemask(BUTTON1_CLICKED, NULL);
    keypad(stdscr, TRUE);
    return;
}

void get_mouse(Vec* vec){
    MEVENT event;
    if (getmouse(&event) == OK) {
        printf("%d %d\n", event.x, event.y);
        printf("HELLO WORLD\n");
        mvprintw(1,1,"hello: %d %d", event.x, event.y);
    }
    return;
}

