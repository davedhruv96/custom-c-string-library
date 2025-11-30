My Custom C String Library

This is my manual implementation of the standard C string library. I built this from scratch because I wanted to actually understand how C handles memory and strings under the hood, rather than just blindly using <string.h>.

Why I Did This

Honestly, pointers and memory management in C were confusing me. I realized the best way to learn wasn't just reading about malloc and free, but actually building the tools that use them.

So, I decided to rebuild the standard library functions myself to figure out:

How pointers actually work: Passing arrays, pointer arithmetic, and dereferencing.

Why C is "unsafe": I learned the hard way why gets() is dangerous and how easy it is to accidentally overwrite memory.

Manual Memory Management: Allocating memory on the heap and remembering to free it.

What's Inside

It's not just a copy-paste of the standard library. I tried to make a few things safer where I could.

Dynamic Memory: The program asks you for the string size and allocates exactly that much memory using malloc.

getstring() (My gets replacement): I added my own input function because standard scanf and gets were giving me headaches with buffer overflows and leftover newline characters. Mine cleans the buffer automatically and prevents you from typing past the allocated size.

The Classics: I manually wrote the logic for:

strlength (Length)

strcopy, strcats, strncats (Copying/Concatenating)

strcompare (Comparing)

strreverse, strlower, strupper (Modifying)

How to Run It

If you want to test it out, you can compile the files together using gcc:

gcc main.c mystring.c -o my_string_lib
./my_string_lib
