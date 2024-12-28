#include "board.h"

int flag(Board* board, Vec vec){
    if (board->visible_state[vec.x][vec.y] != Flag){
        board->visible_state[vec.x][vec.y] = Flag;
    }
    else {
        board->visible_state[vec.x][vec.y] = Hidden;
    }
    return Flag;
}

int check_cell(Board* board, Vec vec){
    // Check if out of bounds
    if (vec.x < 0 || vec.x >= board->width){
        return 0;
    }
    if (vec.y < 0 || vec.y >= board->height){
        return 0;
    }
    
    // Check if a mine 
    return board->real_state[vec.x][vec.y] == Mine;
}

int get_surrounding(Board* board, Vec vec){
    int score = 0;

    score += check_cell(board, (Vec) {vec.x,   vec.y+1}); //top
    score += check_cell(board, (Vec) {vec.x+1, vec.y+1}); //top-right
    score += check_cell(board, (Vec) {vec.x+1, vec.y  }); //right
    score += check_cell(board, (Vec) {vec.x+1, vec.y-1}); //bottom-right
    score += check_cell(board, (Vec) {vec.x,   vec.y-1}); //bottom
    score += check_cell(board, (Vec) {vec.x-1, vec.y-1}); //bottom-left
    score += check_cell(board, (Vec) {vec.x-1, vec.y  }); //left
    score += check_cell(board, (Vec) {vec.x-1, vec.y+1}); //top-left

    return score;
}

int uncover(Board* board, Vec vec){
    // Check if flag (skip)
    if (board->visible_state[vec.x][vec.y] == Flag){
        return Flag;
    }

    // Check if mine
    if (board->real_state[vec.x][vec.y] == Mine){
        board->visible_state[vec.x][vec.y] = Mine;
        return Mine;
    }

    // Otherwise, uncover the visible state with a number
    int state = get_surrounding(board, vec);
    board->visible_state[vec.x][vec.y] = state;

    char msg[128];
    sprintf(msg, "State uncovered at: %d %d, value=%d", vec.x, vec.y, state);
    log(Debug, msg);
    return state;
}

int ff_uncover(Board* board, Vec vec){
    // base case: out of bounds
    if (vec.x < 0 || vec.x >= board->width){
        return 0;
    }
    if (vec.y < 0 || vec.y >= board->height){
        return 0;
    }

    // base case: is already uncovered
    if (!board->is_hidden(board, vec)){
        return  Hidden;
    }

    // uncover self
    int cell_value = uncover(board, vec);

    // recurse if a 0
    if (cell_value == Empty){
        ff_uncover(board, (Vec) {vec.x,   vec.y+1}); //top
        ff_uncover(board, (Vec) {vec.x+1, vec.y+1}); //top-right
        ff_uncover(board, (Vec) {vec.x+1, vec.y  }); //right
        ff_uncover(board, (Vec) {vec.x+1, vec.y-1}); //bottom-right
        ff_uncover(board, (Vec) {vec.x,   vec.y-1}); //bottom
        ff_uncover(board, (Vec) {vec.x-1, vec.y-1}); //bottom-left
        ff_uncover(board, (Vec) {vec.x-1, vec.y  }); //left
        ff_uncover(board, (Vec) {vec.x-1, vec.y+1}); //top-left
    }
    return cell_value;
}

void uncover_all(Board* board){
    for(int i = 0; i < board->width; i++){
        for(int j = 0; j < board->height; j++){
            uncover(board, (Vec) {i, j});
        }
    }
}

void print(Board* board){
    char msg[(MAX_WIDTH * MAX_HEIGHT * 2) + 128];
    strcpy(msg, "\n");

    for(int i = 0; i < board->width; i++){
        for(int j = 0; j < board->height; j++){
            if(board->real_state[i][j] == Mine){
                strcat(msg, "M ");
            }
            else{
                strcat(msg, "_ ");
            }
        }
        strcat(msg, "\n");
    }
    strcat(msg, "\n");

    log(Debug, msg);
}

bool is_valid(Board* board, Vec p){
    return p.x >= 0 && p.x < board->width && p.y >= 0 && p.y < board->height;
}

bool is_hidden(Board* board, Vec p){
    return board->visible_state[p.x][p.y] == Hidden || board->visible_state[p.x][p.y] == Flag;
}

void generate_mines(Board* board){
    srand(time(NULL));
    int mines_placed = 0;
    while(mines_placed < board->mines_num) {
        int rand_x = rand() % board->width;
        int rand_y = rand() % board->height;

        if(board->real_state[rand_x][rand_y] == Empty){
            board->real_state[rand_x][rand_y] = Mine;
            mines_placed++;
        }
    }
    log(Info, "All mines placed.");
}

void init_board(Board* board, int width, int height, int difficulty){
    // Allocate memory and initialise state
    board->real_state = (int**) malloc(sizeof(int*) * width);
    board->visible_state= (int**) malloc(sizeof(int*) * width);
    for(int i = 0; i < width; i++) {
        board->real_state[i] = (int*) malloc(sizeof(int) * height);
        board->visible_state[i] = (int*) malloc(sizeof(int) * height);
        for(int j = 0; j < height; j++){
            board->real_state[i][j] = Empty;
            board->visible_state[i][j] = Hidden;
        }
    }

    // Assign member variables
    board->width = width;
    board->height = height;
    board->flag = flag;
    board->uncover = uncover;
    board->ff_uncover =ff_uncover;
    board->uncover_all = uncover_all;
    board->print = print;
    board->is_valid = is_valid;
    board->is_hidden = is_hidden;

    int num_of_cells = board->width * board->height;
    const float diff_modifer = 7.8f; // higher skews the difficulty down
    board->mines_num = ((float) num_of_cells) / (diff_modifer - ((float) difficulty));

    // Place mines
    generate_mines(board);

    char msg[128] ;
    sprintf(msg, "Board initialised with width=%d, height=%d, mines=%d", 
        board->width, board->height, board->mines_num);
    log(Info, msg);
}

void free_board(Board* board){
    for(int i = 0; i < board->width; i++) {
        free(board->real_state[i]);
        free(board->visible_state[i]);
    }
    free(board->real_state);
    free(board->visible_state);
    log(Info, "Board freed.");
}
