#ifndef MYSTRING_H
#define MYSTRING_H

typedef struct{
    char *data;
    size_t nullCharIndex;
    size_t capacity;
} DynamicString;

int getstring(DynamicString *s); //returns 0 for success, -1 if malloc fails

//core functions, almost same as original just more safe ;)
size_t strlength(char*);
void strcopy(DynamicString*, DynamicString*);
int strcompare(DynamicString*, DynamicString*);
void strcats(DynamicString*, DynamicString*);
void strncats(DynamicString*, DynamicString*, size_t);
void strreverse(DynamicString*);
void strlower(DynamicString*);
void strupper(DynamicString*);

//main memory leak checker
int ensureCapacity(DynamicString*, size_t);

//constructor destructor
DynamicString* createString(size_t initial_size);
void destroyString(DynamicString* s);

#endif