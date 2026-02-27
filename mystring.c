#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"

DynamicString* createString(size_t initial_size){ //constructor
    DynamicString *s = malloc(sizeof(DynamicString));
    if(!s){
        return NULL;
    }
    
    s->data = malloc(initial_size);
    if(!s->data){
        return NULL;
    }
    s->capacity = initial_size;
    s->nullCharIndex = 0;
    s->data[0] = '\0';
    return s;
}

int getstring(DynamicString *s)
{
    int i = 0;
    while (1)
    {
        if (i == s->capacity - 1)
        {
            if(ensureCapacity(s, s->capacity*2) == 0){
                s->data[i] = '\0';
                s->nullCharIndex = i;
                printf("Memory allocation failed!");
                return -1;
            }
            continue;
        }
        if (scanf("%c", &s->data[i]) == EOF)
        {
            s->data[i] = '\0';
            s->nullCharIndex = i;
            return 0;
        }
        if (i == 0 && s->data[i] == '\n')
        {
            continue;
        }
        if (s->data[i] == '\n')
        {
            s->data[i] = '\0';
            s->nullCharIndex = i;
            return 0;
        }
        i++;
    }
}

size_t strlength(char *s1)
{
    if (s1 == NULL)
    {
        return 0;
    }
    size_t len = 0;
    while(s1[len] != '\0'){
        len++;
    }
    return len;
}

void strcopy(DynamicString *s1, DynamicString *s2)
{
    if (s1->data == NULL || s2->data == NULL)
    {
        return;
    }
    int i;
    if(ensureCapacity(s1, s2->capacity)){
        for (i = 0; i < s2->nullCharIndex; i++)
        {
            s1->data[i] = s2->data[i];
        }
        s1->data[i] = '\0';
        s1->nullCharIndex = s2->nullCharIndex;
    }
    else{
        printf("Memory allocation failed!");
    }
    
}

int strcompare(char* s1, char* s2)
{
    if (s1 == NULL && s2 == NULL)
    {
        return 1;
    }
    int len1 = strlength(s1);
    int len2 = strlength(s2);
    if (len1 != len2)
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < len1; i++)
        {
            if (s1[i] != s2[i])
            {
                return 0;
            }
        }
    }
    return 1;
}

void strcats(DynamicString *s1, DynamicString *s2)
{
    if (s2 == NULL)
    {
        return;
    }
    if(ensureCapacity(s1, s1->capacity + s2->capacity)){
        int i;
        for (i = 0; i <= s2->nullCharIndex; i++)
        {
            s1->data[s1->nullCharIndex + i] = s2->data[i];
        }
        s1->nullCharIndex += (i - 1);
    }
    else{
        printf("Memory allocation failed!");
        return;
    }
}

void strncats(DynamicString *s1, DynamicString *s2, size_t n)
{
    if (s2 == NULL)
    {
        return;
    }

    int i;
    if(ensureCapacity(s1, s1->capacity + s2->capacity + (size_t)n)){
        for (i = 0; i < n && s2->data[i] != '\0'; i++)
        {
            s1->data[s1->nullCharIndex + i] = s2->data[i];
        }
        s1->data[s1->nullCharIndex + i] = '\0';
        s1->nullCharIndex += i;
    }
    else{
        printf("Memory allocation failed!");
        return;
    }
    
}

void strreverse(char* s1)
{
    if (s1 == NULL)
    {
        return;
    }
    char temp;
    int len = strlength(s1);
    for (int i = 0; i < len / 2; i++)
    {
        temp = s1[i];
        s1[i] = s1[len - i - 1];
        s1[len - i - 1] = temp;
    }
}

void strlower(char* s1)
{
    if (s1 == NULL)
    {
        return;
    }
    for(int i=0; s1[i] != '\0'; i++)
    {
        if (s1[i] >= 'A' && s1[i] <= 'Z')
        {
            s1[i] += 32;
        }
    }
}

void strupper(char* s1)
{
    if (s1 == NULL)
    {
        return;
    }
    for(int i=0; s1[i] != '\0'; i++)
    {
        if (s1[i] >= 'a' && s1[i] <= 'z')
        {
            s1[i] -= 32;
        }
    }
}

int ensureCapacity(DynamicString *s, size_t new_capacity){
    if(s->capacity >= new_capacity){
        return 1;
    }
    
    char *temp = realloc(s->data, new_capacity);
    if(temp == NULL){
        return 0;
    }

    s->data = temp;
    s->capacity = new_capacity;

    return 1;
}

void destroyString(DynamicString* s){
    if(s){
        free(s->data);
        free(s);
    }
}