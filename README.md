# My Custom C String Library

This is my manual implementation of the standard C string library. I built this from scratch because I wanted to actually understand how C handles memory and strings under the hood, rather than just blindly using `<string.h>`.

## Why I Did This

Honestly, pointers and memory management in C were confusing me. I realized the best way to learn wasn't just reading about `malloc` and `free`, but actually building the tools that use them.

So, I decided to rebuild the standard library functions myself to figure out:

- **Mastering Pointers**: Figuring out exactly how arrays and pointers interact.
- **Safety First**: Implementing bounds checking manually because standard `gets()` is dangerous.
- **Memory Management**: Getting comfortable with `malloc` and `free` for dynamic string sizes.

## Features

- **Dynamic Memory**: Handles user-defined string sizes on the heap so you aren't stuck with fixed-size arrays.
- **Safe Input**: I added a custom `getstring()` function (my version of `gets`). It handles input buffering and prevents buffer overflow.
- **Core Functions**:
  - `strlength`: Calculate length.
  - `strcopy` / `strcats` / `strncats`: Safe copying and concatenation.
  - `strcompare`: Manual character comparison.
  - `strreverse` / `strlower` / `strupper`: In-place string manipulation.

