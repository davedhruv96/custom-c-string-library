CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

execute: main.c src/mystring.c src/arena.c src/gc.c src/vm.c src/stringlib.c
	$(CC) $(CFLAGS) -o execute main.c src/mystring.c src/arena.c src/gc.c src/vm.c src/stringlib.c

debug:
	gdb ./execute
	
memCheck: execute
	valgrind --leak-check=full -s --show-leak-kinds=all ./execute

clean: execute
	rm -f execute

