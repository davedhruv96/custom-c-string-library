#ifndef MYSTRING_H
#define MYSTRING_H

typedef struct{
    char *data;
    size_t nullCharIndex;
    size_t capacity;
} DynamicString;

int getstring(DynamicString *s);
DynamicString* createString(size_t initial_size);

size_t strlength(char*);
void strcopy(DynamicString*, DynamicString*);
int strcompare(char*, char*);
void strcats(DynamicString*, DynamicString*);
void strncats(DynamicString*, DynamicString*, size_t);
void strreverse(char*);
void strlower(char*);
void strupper(char*);
int ensureCapacity(DynamicString*, size_t);
void destroyString(DynamicString* s);

#endif