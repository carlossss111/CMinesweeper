#pragma once

#include <getopt.h>

#include "common.h"
#include "logging.h"
#include "graphics.h"
#include "mouse.h"
#include "board.h"

#define HELP_MESSAGE "./cminesweeper [option]\n\
    -h          = print this help message\n\
    -W <number> = start with board of width <number>\n\
    -H <number> = start with board of height <height>\n\
    -D <1-9>    = difficulty, 1 = minimum, 9 = maximum\n"
