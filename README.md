# custom-c-string-library

A chill, from-scratch remake of `<string.h>` — written while I was trying to actually understand pointers, string,  `malloc` and why C can be weirdly unforgiving.

Think of this as a uni project meets tinkering session: I rebuilt a handful of classic C string functions with some simple safety-minded tweaks and lots of hand-written logic.

Why I did this
--------------
I kept getting confused by pointers and buffer overflows in class, and reading slides wasn't cutting it. So I decided to:
- actually write the functions people use every day (`strlen`, `strcpy`, `strcat`, etc.),
- learn how dynamic allocation behaves in real code,
- and see where the standard API can be “dangerous” if used carelessly.

What I learned (and what you can see in the code)
-------------------------------------------------
- How pointer arithmetic and passing arrays to functions really work.
- Why functions like `gets()` are dangerous and how leftover newline characters can mess input.
- How to allocate exactly what you need with `malloc` and manage the memory manually.

What’s in this repo
-------------------
- `mystring.c` / `mystring.h` — manual implementations of several `<string.h>` functions, plus some safer helpers.
- `main.c` — simple interactive demo (asks for sizes, reads strings, shows function outputs).
- A custom `getstring()` — a safer replacement for `gets()` that handles buffer length and leftover newlines.
- Implemented functions: `strlength` (`strlen`), `strcopy` (`strcpy`), `strcats`/`strncats` (`strcat`/`strncat`), `strcompare` (`strcmp`), `strreverse`, `strlower`, `strupper`, and a couple of helpers.

Features & design notes
-----------------------
- Dynamic memory: demo asks you for the size, then allocates exactly that much.
- Input handling: `getstring()` tries to avoid common pitfalls with `scanf`/`gets` by cleaning the input buffer.
- Educational: code is intentionally straightforward (no clever macros) so it’s easier to follow for learning.

How to compile & run
--------------------
Compile everything with GCC (same folder):
```bash
gcc main.c mystring.c -o my_string_lib
./my_string_lib
```

TL;DR (if you’re skimming)
--------------------------
I rewrote parts of the C string library to learn how it all works. It’s simple, verbose, and meant for learning — not production use. Play around, break it, then fix it again.
