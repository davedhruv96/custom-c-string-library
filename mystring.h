#ifndef MYSTRING_H
#define MYSTRING_H


int getstring(char s1[], int stringSize);


int strlength(char s1[]);
void strcopy(char s1[], char s2[]);
int strcompare(char s1[], char s2[]);
void strcats(char s1[], char s2[]);
void strncats(char s1[], char s2[], int n);
void strreverse(char s1[]);
void strlower(char s1[]);
void strupper(char s1[]);

#endif