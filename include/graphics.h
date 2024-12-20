#pragma once

#include <curses.h>

#include "common.h"
#include "logging.h"
#include "board.h"
#include "game.h"

#define init_color_pairs() \
    start_color();\
    init_pair(0, COLOR_WHITE, COLOR_BLACK);\
    init_pair(1, COLOR_BLUE, COLOR_BLACK);\
    init_pair(2, COLOR_GREEN, COLOR_BLACK);\
    init_pair(3, COLOR_RED, COLOR_BLACK);\
    init_pair(4, COLOR_CYAN, COLOR_BLACK);\
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);\
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);\
    init_pair(7, COLOR_BLACK, COLOR_BLACK);\
    init_pair(8, COLOR_BLACK, COLOR_BLACK);\
    init_pair(Hidden, COLOR_WHITE, COLOR_WHITE);\
    init_pair(Flag, COLOR_RED, COLOR_WHITE);\
    init_pair(Mine, COLOR_RED, COLOR_WHITE);\
    clear()
#define is_valid_color(x) (x >= Empty && x <= Mine)

typedef struct Graphics {
    int term_width;
    int term_height;

    bool (*term_is_large_enough) (struct Graphics* self, Board* board);
    void (*draw_board) (struct Graphics* self, Board* board, Game* game);
}Graphics;


bool term_is_large_enough (struct Graphics* self, Board* board);
void draw_board(Graphics* graphics, Board* board, Game* game);

void init_graphics(Graphics* graphics);
void finish_graphics(Graphics* graphics);

