#include "main.h"

int parse_args(int argc, char** argv, int* width, int* height, int* difficulty){
    int c;

    char error_text[1028];
    char* error_text_ptr = error_text;
    *error_text_ptr = '\0';
    while((c = getopt(argc, argv, "hsH:W:D:")) != -1){
        switch(c) {
            case 'h': // Help
                printf(HELP_MESSAGE);
                return 1;

            case 's': // Screensaver
                printf("STUB \n");
                break;

            case 'W': // Width
                *width = strtol(optarg, NULL, 10);
                if(*width > MAX_WIDTH){
                    error_text_ptr += sprintf(error_text_ptr, 
                    "Width %d exceeds maximum width %d.\n", *width, MAX_WIDTH);
                }
                if(*width< MIN_WIDTH){
                    error_text_ptr += sprintf(error_text_ptr, 
                    "Width %d is less than minimum width %d.\n", *width, MIN_WIDTH);
                }
                break;

            case 'H': // Height
                *height = strtol(optarg, NULL, 10);
                if(*height > MAX_HEIGHT){
                    error_text_ptr += sprintf(error_text_ptr, 
                    "Height %d exceeds maximum height %d.\n", *height, MAX_HEIGHT);
                }
                if(*height< MIN_HEIGHT){
                    error_text_ptr += sprintf(error_text_ptr,
                    "Height %d is less than minimum height %d.\n", *height, MIN_HEIGHT);
                }
                break;

            case 'D': // Difficulty
                *difficulty = strtol(optarg, NULL, 10);
                if(*difficulty > MAX_DIFFICULTY){
                    error_text_ptr += sprintf(error_text_ptr, 
                    "Difficulty %d exceeds maximum difficulty %d.\n", *difficulty, MAX_DIFFICULTY);
                }
                if(*difficulty < MIN_DIFFICULTY){
                    error_text_ptr += sprintf(error_text_ptr, 
                    "Difficulty %d is less than minimum difficulty %d.\n", *difficulty, MAX_DIFFICULTY);
                }
                break;

            case '?': // Unrecognised
                printf(HELP_MESSAGE);
                return 1;
        }
    }

    if(strlen(error_text)){
        printf("Failed to start!\n\n%s", error_text);
        close_logger();
        return 1;
    }
    return 0;
}

int main(int argc, char** argv) {
    init_logger();

    // Parse arguments
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    int difficulty = DEFAULT_DIFFICULTY;
    if(parse_args(argc, argv, &width, &height, &difficulty) != 0){
        return 1;
    }

    // Inits
    Board board;
    Graphics graphics;
    Vec mouse_pos;
    init_board(&board, width, height, difficulty);
    init_graphics(&graphics);
    init_mouse();
    board.print(&board);

    // Validate board size can be printed
    if(!graphics.term_is_large_enough(&graphics, &board)){
        finish_graphics(&graphics);
        free_board(&board);
        close_logger();
        printf("The board was too large for the terminal window!\n");
        return 1;
    }

    // Game Loop
    for(;;){
        graphics.draw_board(&graphics, &board, NULL);
        get_mouse(&mouse_pos);
        graphics.to_board_vec(&graphics, &board, &mouse_pos);
        if (board.position_is_valid(&board, mouse_pos)){
            board.uncover(&board, mouse_pos);
        }
    }
    
    // Frees
    finish_graphics(&graphics);
    free_board(&board);
    close_logger();

    return 0;
}
