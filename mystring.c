#include <stdio.h>
#include "mystring.h"

void getstring(char s1[], int stringSize)
{
    int i = 0;
    while (1)
    {
        if (i == stringSize - 1)
        {
            s1[i] = '\0';
            break;
        }
        scanf("%c", &s1[i]);

        if (i == 0 && s1[i] == '\n')
        {
            continue;
        }
        if (s1[i] == '\n')
        {
            s1[i] = '\0';
            break;
        }
        i++;
    }
}

int strlength(char s1[])
{
    int len = 0;
    for (int i = 0; s1[i] != '\0'; i++)
    {
        len++;
    }
    return len;
}

void strcopy(char s1[], char s2[])
{
    int i;
    int len = strlength(s1);
    for (i = 0; i < len; i++)
    {
        s2[i] = s1[i];
    }
    s2[i] = '\0';
}

int strcompare(char s1[], char s2[])
{
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

void strcats(char s1[], char s2[])
{
    int i;
    int len = strlength(s1);
    for (i = 0; s2[i] != '\0'; i++)
    {
        s1[len + i] = s2[i];
    }
    s1[len + i] = '\0';
}

void strncats(char s1[], char s2[], int n)
{
    int i;
    int len = strlength(s1);
    for (i = 0; i < n && s2[i] != '\0'; i++)
    {
        s1[len + i] = s2[i];
    }
    s1[len + i] = '\0';
}

void strreverse(char s1[])
{
    char temp;
    int len = strlength(s1);
    for (int i = 0; i < len / 2; i++)
    {
        temp = s1[i];
        s1[i] = s1[len - i - 1];
        s1[len - i - 1] = temp;
    }
}

void strlower(char s1[])
{
    for (int i = 0; s1[i] != '\0'; i++)
    {
        if (s1[i] >= 'A' && s1[i] <= 'Z')
        {
            s1[i] += 32;
        }
    }
}

void strupper(char s1[])
{
    for (int i = 0; s1[i] != '\0'; i++)
    {
        if (s1[i] >= 'a' && s1[i] <= 'z')
        {
            s1[i] -= 32;
        }
    }
}