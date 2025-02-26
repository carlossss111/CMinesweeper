# Daniel 2024
EXECUTABLE_PATH = bin/cminesweeper

PREFIX  = 
CC	 	= gcc
CFLAGS  = -std=c17 -Wall -g
LDFLAGS = -lncurses
DFLAGS  = 
SRC     = src/*.c
INCLUDE = include/
MFLAGS  = --suppressions=misc/ncurses_6_5.supp

compile:
	$(PREFIX)$(CC) $(CFLAGS) $(DFLAGS) $(LDFLAGS) $(SRC) -I$(INCLUDE) -o $(EXECUTABLE_PATH)

run: compile
	$(EXECUTABLE_PATH) $(ARGS)

memcheck: compile
	/usr/bin/valgrind $(MFLAGS) $(EXECUTABLE_PATH) $(ARGS)

clean:
	rm -r bin/*

install: compile
	sudo ln -f $(EXECUTABLE_PATH) /usr/local/bin/cminesweeper

uninstall:
	sudo rm /usr/local/bin/cminesweeper

