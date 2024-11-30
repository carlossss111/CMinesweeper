#pragma once

#include "common.h"
#include "logging.h"

typedef struct Game{
    int time;
    int score;

    void (*add_score) (struct Game* self, int last_uncovered);
    bool (*is_gameover) (int last_uncovered);
}Game;

void add_score(Game* game, int last_uncovered);
bool is_gameover(int last_uncovered);

void init_game(Game* game);
