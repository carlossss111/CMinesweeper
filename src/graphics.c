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

void to_real_vec(struct Graphics* graphics, Board* board, Vec* vec){
    vec->x = vec->x + (graphics->term_width - board->width)/2;
    vec->y = vec->y*2 + (graphics->term_height - board->height*2)/2;
}

void to_board_vec(struct Graphics* graphics, Board* board, Vec* vec){
    vec->x = vec->x - (graphics->term_width - board->width)/2;
    vec->y = vec->y/2 - (graphics->term_height - board->height*2)/4;
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
            Vec vec = {i, j};
            graphics->to_real_vec(graphics, board, &vec);
            draw_cell(vec, board->visible_state[i][j]);
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
    graphics->to_real_vec = to_real_vec;
    graphics->to_board_vec = to_board_vec;
    graphics->term_is_large_enough = term_is_large_enough;

    char msg[256];
    sprintf(msg, "Graphics initialised with width=%d, height=%d", width, height);
    log(Info, msg);
} 

void finish_graphics(Graphics* graphics){
    // Close Ncurses window
    endwin();
    delwin(stdscr);
    log(Info, "Graphics cleaned up.");
}
