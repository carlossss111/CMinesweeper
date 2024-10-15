#include "graphics.h"

// Init the ncurses window and colours
void graphics_init(){
    initscr();

    if(has_colors() == FALSE){
        endwin();
        printf("It is the 243rd decade and your terminal does not " 
               "support colour. Tough luck.\n");
        exit(1);
    }
    init_color_pairs();
} 

// Close the ncurses window
void graphics_finish(){
    endwin();
}

// Draw a cell by passing in the number of adjacent mines
void draw_cell(int cell_state, Position pos){
    if (!is_valid_color(cell_state)){
        return;
    }

    attron(COLOR_PAIR(cell_state));
    attron(A_BOLD);

    mvaddch(pos.x, pos.y, cell_state + '0');

    attroff(A_BOLD);
    attroff(COLOR_PAIR(cell_state));
}
    

