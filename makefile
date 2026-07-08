CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

execute: main.c include/mystring.c include/arena.c include/gc.c
	$(CC) $(CFLAGS) -o execute main.c include/mystring.c include/arena.c include/gc.c



clean: execute
	rm -f execute

