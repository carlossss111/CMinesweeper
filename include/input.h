#pragma once

#include <ncurses.h>

#include "common.h"
#include "logging.h"

#define LEFT_CLICKED BUTTON1_CLICKED
#define RIGHT_CLICKED BUTTON3_CLICKED

#define ESC_KEY 27
#define Q_KEY 'q'
#define R_KEY 'r'

void init_mouse();
void get_input(Vec* vec, bool* right_click, int* key);
