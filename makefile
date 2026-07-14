CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

execute: main.c lib/mystring.c lib/arena.c lib/gc.c lib/vm.c lib/strlib.c
	$(CC) $(CFLAGS) -o execute main.c lib/mystring.c lib/arena.c lib/gc.c lib/vm.c lib/strlib.c

debug:
	gdb ./execute
	
memCheck: execute
	valgrind --leak-check=full -s --show-leak-kinds=all ./execute

clean: execute
	rm -f execute

