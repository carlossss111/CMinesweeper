#pragma once

#include "common.h"
#include "logging.h"

#define MIN_WIDTH 3
#define DEFAULT_WIDTH 15
#define MAX_WIDTH 20 

#define MIN_HEIGHT 3
#define DEFAULT_HEIGHT 10
#define MAX_HEIGHT 50

#define MIN_DIFFICULTY 1
#define DEFAULT_DIFFICULTY 3
#define MAX_DIFFICULTY 5

typedef struct Board{
    int** real_state;
    int** visible_state;
    int width;
    int height;
    int mines_num;

    int (*flag) (struct Board* self, Vec position);
    int (*uncover) (struct Board* self, Vec position);
    int (*ff_uncover) (struct Board* self, Vec position);
    void (*uncover_all) (struct Board* self);
    void (*print) (struct Board* self);
    bool (*is_valid) (struct Board* self, Vec position);
    bool (*is_hidden) (struct Board* self, Vec position);
}Board;

int flag(Board* board, Vec position);
int uncover(Board* board, Vec position);
int ff_uncover(Board* board, Vec position);
void uncover_all(Board* board);
void print(Board* board);
bool is_valid(Board* board, Vec position);
bool is_hidden(Board* board, Vec position);

void init_board(Board* unitinitialised_board, int width, int height, int difficulty);
void free_board(Board* finished_board);
