#include "board.h"

int flag(Board* board, Vec vec){
    board->visible_state[vec.x][vec.y] = Flag;
    return Flag;
}

int uncover(Board* board, Vec vec){
    board->visible_state[vec.x][vec.y] = board->real_state[vec.x][vec.y];
    char msg[128];
    sprintf(msg, "State uncovered at: %d %d", vec.x, vec.y);
    log(Debug, msg);
    return board->real_state[vec.x][vec.y];
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

bool position_is_valid(Board* board, Vec p){
    return p.x >= 0 && p.x < board->width && p.y >= 0 && p.y < board->height;
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
    board->uncover_all = uncover_all;
    board->print = print;
    board->position_is_valid = position_is_valid;

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
