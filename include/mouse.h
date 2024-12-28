#pragma once

#include <ncurses.h>

#include "common.h"
#include "logging.h"

#define LEFT_CLICKED BUTTON1_CLICKED
#define RIGHT_CLICKED BUTTON3_CLICKED

void init_mouse();
void get_mouse(Vec* vec, bool* right_click);
