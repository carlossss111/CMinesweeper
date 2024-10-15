# Daniel 2024
EXECUTABLE_PATH = bin/cminesweeper

PREFIX  = 
CC	 	= gcc
CFLAGS  = -std=c17 -Wall 
LDFLAGS = -lncurses
DFLAGS  = 
SRC     = src/*.c
INCLUDE = include/

compile:
	$(PREFIX)$(CC) $(CFLAGS) $(DFLAGS) $(LDFLAGS) $(SRC) -I$(INCLUDE) -o $(EXECUTABLE_PATH)

run: compile
	$(EXECUTABLE_PATH) $(ARGS)

clean:
	rm -r bin/*

