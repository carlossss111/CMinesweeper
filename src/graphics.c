#include "graphics.h"

// Init the ncurses window and colours
void init_graphics(){
    initscr();

    if(has_colors() == FALSE){
        endwin();
        printf("It is the 243rd decade and your terminal does not " 
               "support colour. Tough luck.\n");
        exit(1);
    }
    init_color_pairs();

    log(Info, "Graphics initialised.");
} 

// Close the ncurses window
void finish_graphics(){
    endwin();

    log(Info, "Graphics cleaned up.");
}

// Draw a cell by passing in the number of adjacent mines
void draw_cell(int cell_state, Vec vec){
    if (!is_valid_color(cell_state)){
        return;
    }

    attron(COLOR_PAIR(cell_state));
    attron(A_BOLD);

    mvaddch(vec.x, vec.y, cell_state + '0');

    attroff(A_BOLD);
    attroff(COLOR_PAIR(cell_state));
}
    

