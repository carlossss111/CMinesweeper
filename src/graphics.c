#include "graphics.h"

// Draw a cell by passing in the number of adjacent mines
void draw_cell(Vec vec, int cell_state){
    if (!is_valid_color(cell_state)){
        return;
    }

    attron(COLOR_PAIR(cell_state));
    attron(A_BOLD);

    char c;
    if (cell_state == Mine) {
        c = 'M';
    }
    else if (cell_state == Flag) {
        c = 'F';
    }
    else if (cell_state == Empty) {
        c = '.';
    }
    else{
        c = '0' + cell_state;
    }
    mvaddch(vec.x, vec.y, c);
    mvaddch(vec.x, vec.y+1, ' ');

    attroff(A_BOLD);
    attroff(COLOR_PAIR(cell_state));
}

void draw_board(Graphics* graphics, Board* board, Game* game){
    // Check for terminal resizing
    int new_term_width, new_term_height;
    getmaxyx(stdscr, new_term_width, new_term_height);
    if(new_term_width != graphics->term_width || new_term_height != graphics->term_height){
        graphics->term_width = new_term_width;
        graphics->term_height = new_term_height;
        clear();
    }

    // Draw board
    for(int i = 0; i < board->width; i++){
        for(int j = 0; j < board->height; j++){
            int real_x = i + (graphics->term_width - board->width)/2;
            int real_y = j*2 + (graphics->term_height - board->height*2)/2;

            draw_cell((Vec) {real_x, real_y}, board->visible_state[i][j]);
        }
    }
    refresh();
}

bool term_is_large_enough (Graphics* graphics, Board* board){
    return graphics->term_width >= board->width && graphics->term_height >= board->height*2;
}

void init_graphics(Graphics* graphics){
    // Init Ncurses
    initscr();
    if(has_colors() == FALSE){
        endwin();
        printf("It is the 243rd decade and your terminal does not " 
               "support colour. Tough luck.\n");
        close_logger();
        exit(1);
    }
    init_color_pairs();

    // Init graphics struct
    int width, height;
    getmaxyx(stdscr, width, height);
    graphics->term_width = width;
    graphics->term_height = height;
    graphics->draw_board = draw_board;
    graphics->term_is_large_enough = term_is_large_enough;

    log(Info, "Graphics initialised.");
} 

void finish_graphics(Graphics* graphics){
    // Close Ncurses window
    endwin();

    log(Info, "Graphics cleaned up.");
}
