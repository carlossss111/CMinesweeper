#pragma once

#include "common.h"
#include "logging.h"

typedef struct Board{
    int** real_state;
    int** visible_state;

    int (*flag) (struct Board* self, Vec position);
    int (*uncover) (struct Board* self, Vec position);
    void (*uncover_all) (struct Board* self);
    void (*print) (struct Board* self);
}Board;

int flag(Board* board, Vec position);
int uncover(Board* board, Vec position);
void uncover_all(Board* board);
void print(Board* board);

void init_board(Board* unitinitialised_board, int width, int height);
void free_board(Board* finished_board);
