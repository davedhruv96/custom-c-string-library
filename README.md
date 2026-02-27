# Custom C String Library

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/davedhruv96/custom-c-string-library/actions) <!-- Placeholder; add CI if set up -->
[![Language: C](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))

Hey there! 👋 This is a simple, from-scratch take on some key `<string.h>` functions in C. I made it because C strings and pointers can be a bit tricky at first, and I wanted a hands-on way to get comfortable with them. Think of it as a cozy learning buddy—nothing fancy, just helpful tools with a focus on keeping things safe and straightforward.

## Why I Built This

Back when I started with C, I kept wondering: "What's really happening under the hood with `malloc` or string copies?" So, I rolled up my sleeves and rebuilt these basics myself. It helped me:
- **Get comfy with pointers**: How they team up with arrays and memory.
- **Add some safety nets**: Like a custom input function that won't let buffers overflow (looking at you, old `gets()`!).
- **Play with dynamic sizing**: Strings that grow as needed, without the hassle of fixed arrays.

If you're in the same boat—learning C and wanting to peek behind the curtain—this might be a fun sidekick. No pressure, though!

## Features

It's got the essentials, with a gentle emphasis on not crashing your program:
- **Flexible Sizing**: Handles growing strings on the fly with `realloc`.
- **Gentle Input**: `getstring()` reads safely, with a heads-up if things get too full.
- **Handy Functions**:
  - `strlength(char *s)`: Counts chars (plays nice with NULL).
  - `strcopy(char *src, char *dest)`: Copies over carefully.
  - `strcompare(char *s1, char *s2)`: Checks if they're a match (case-sensitive, quick length check first).
  - `strcats(char *dest, char *src)`: Tacks src onto dest (smart length calc inside).
  - `strncats(char *dest, char *src, int n)`: Adds up to n chars from src.
  - `strreverse(char *s)`: Flips it around in place.
  - `strlower(char *s)` / `strupper(char *s)`: Shifts case (keeps it simple for ASCII).
- **Error-Friendly**: Spots memory hiccups and bows out gracefully.

## Quick Start

1. Grab the code:
   ```
   git clone https://github.com/davedhruv96/custom-c-string-library.git
   cd custom-c-string-library
   ```

2. Build it (GCC or Clang works great):
   ```
   gcc -O2 main.c mystring.c -o my_string_lib
   ```

3. Fire it up:
   ```
   ./my_string_lib
   ```

## How to Play Around

It pops open a friendly menu to try things out:

```
--- Welcome to the Custom C String Library ---
Enter max chars (incl. null): 100
Enter first string: Hello World

Current String 1: "Hello World"
1. Find length of S1
2. Copy S1 into S2 (and print S2)
...
Enter choice: 1
Length of S1: 11
```

- Strings grow automatically when you concat or resize.
- Mess up an input? It'll nudge you to try again—no drama.

Want to use it in your own code? Just `#include "mystring.h"` and link `mystring.c`. Quick example:
```c
#include "mystring.h"
char *buf = malloc(50);
getstring(buf, 50);
printf("Len: %d\n", strlength(buf));
free(buf);
```

## Testing It Out

There's a little test suite to poke at the edges (empty strings, NULLs, etc.):
```
gcc test_suite.c mystring.c -o test_suite
./test_suite
```
It should zip through with a cheerful "All passed!"—and no memory leaks in sight.

## A Few Notes

- **ASCII Focus**: Keeps things simple—no fancy Unicode support yet.
- **Resize Reminder**: The lib assumes you've got space for appends (like in the demo); std lib does too.

## Let's Team Up

Got ideas? Bugs? More functions like `strfind`? I'd love to hear—open a pull request or issue. Check [CONTRIBUTING.md](CONTRIBUTING.md) for easy tips.

## License

MIT—use it freely! © Dhruv Dave(https://github.com/davedhruv96). Full deets in [LICENSE](LICENSE).

---

## Note

There are many things i want to improve in this project. And i have decided to not do that right now and upgrade it as i need it in my future projects.

Thanks for stopping by—hope this makes C strings a tad less mysterious. Drop a star if it sparks joy! 🌟 Questions? Just ask.