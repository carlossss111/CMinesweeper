#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Vec;

enum Cell{
    Empty = 0, One = 1, Two = 2, Three = 3, Four = 4, 
    Five = 5, Six = 6, Seven = 7, Eight = 8,
    Hidden, Flag, Mine
};
