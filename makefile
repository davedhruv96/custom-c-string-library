CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

execute: main.c lib/mystring.c lib/arena.c lib/gc.c
	$(CC) $(CFLAGS) -o execute main.c lib/mystring.c lib/arena.c lib/gc.c

debug:
	gdb ./execute
	
mem-leakcheck: execute
	valgrind --leak-check=full -s --show-leak-kinds=all ./execute

clean: execute
	rm -f execute

