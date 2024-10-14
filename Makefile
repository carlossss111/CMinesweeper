# Daniel 2024
PREFIX  = 
CC	 	= gcc
OPTS  	= -std=c17 -Wall -Wextra
INCLUDE = -Iinclude/
NAME 	= cminesweeper

compile:
	$(PREFIX)$(CC) src/*.c -o bin/$(NAME) $(INCLUDE) $(OPTS)

run: compile
	./bin/$(NAME)

clean:
	rm -r bin/*

