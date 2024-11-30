#pragma once

#include <curses.h>

#include "common.h"
#include "logging.h"
#include "board.h"
#include "game.h"

#define init_color_pairs() \
    start_color();\
    init_pair(1, COLOR_BLUE, COLOR_WHITE);\
    init_pair(2, COLOR_GREEN, COLOR_WHITE);\
    init_pair(3, COLOR_RED, COLOR_WHITE);\
    init_pair(4, COLOR_CYAN, COLOR_WHITE);\
    init_pair(5, COLOR_YELLOW, COLOR_WHITE);\
    init_pair(6, COLOR_MAGENTA, COLOR_WHITE);\
    init_pair(7, COLOR_BLACK, COLOR_WHITE);\
    init_pair(8, COLOR_BLACK, COLOR_WHITE);\
    clear()
#define is_valid_color(x) (x >= 1 && x <= 8)

void draw_board(Board* board, Game* game);

void init_graphics();
void finish_graphics();

