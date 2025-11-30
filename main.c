#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"

void main()
{
    int menu, stringSize, n;
    printf("Enter maximum characters for your strings(including null character): ");
    while (scanf("%d", &stringSize) != 1 || stringSize <= 1)
    {
        while (getchar() != '\n')
            ;
        printf("Enter maximum character for the string, string size should be greater than 1: ");
    }
    char *s1 = malloc(stringSize * sizeof(char));
    char *s2 = malloc(stringSize * sizeof(char));

    if (s1 == NULL || s2 == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("\n--- Welcome to the Custom C String Library ---\n");
    printf("Please enter the first string to start: ");
    getstring(s1, stringSize);
    // while (getchar() != '\n');

    while (1)
    {
        printf("\n\n----------------------------------------\n");
        printf("Current String 1: \"%s\"\n", s1);
        printf("----------------------------------------\n");
        printf("1. Find length of S1\n");
        printf("2. Copy S1 into S2 (and print S2)\n");
        printf("3. Compare S1 with a new string (S2)\n");
        printf("4. Concatenate a new string onto S1\n");
        printf("5. Concatenate N characters onto S1\n");
        printf("6. Reverse S1\n");
        printf("7. Lowercase S1\n");
        printf("8. Uppercase S1\n");
        printf("9. Enter a NEW String 1\n");
        printf("0. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        int temp = scanf("%d", &menu);
        while (temp != 1)
        {
            while (getchar() != '\n');
            printf("Menu num is between 0 and 9, reEnter menu: ");
            temp = scanf("%d", &menu);
        }
        switch (menu)
        {
        case 0:
            printf("Exiting...\n");
            free(s1);
            free(s2);
            return;

        case 1:
            printf("Length of S1: %d\n", strlength(s1));
            break;

        case 2:
            strcopy(s1, s2);
            if (!realloc(s2, stringSize*sizeof(char)))
                {
                    free(s1);
                    free(s2);
                    printf("Memory allocation failed!");
                    return;
                }
            printf("Copied! S2 is now: \"%s\"\n", s2);
            break;

        case 3:
            printf("Enter S2 to compare: ");
            getstring(s2, stringSize);
            if (strcompare(s1, s2))
            {
                printf("Result: The strings are IDENTICAL.\n");
            }
            else
            {
                printf("Result: The strings are DIFFERENT.\n");
            }
            break;

        case 4:
            printf("Enter string to append to S1: ");
            getstring(s2, stringSize);
            if (strlength(s1) + strlength(s2) >= stringSize)
            {
                stringSize = strlength(s1) + strlength(s2) + 1;
                if (!realloc(s1, stringSize*sizeof(char)))
                {
                    free(s1);
                    free(s2);
                    printf("Memory allocation failed!");
                    return;
                }
            }
            strcats(s1, s2);
            printf("New S1: \"%s\"\n", s1);
            break;

        case 5:
            printf("Enter string to append: ");
            getstring(s2, stringSize);
            printf("How many characters? ");
            scanf("%d", &n);
            if (strlength(s1) + n * sizeof(char) + 1 >= stringSize)
            {
                stringSize = strlength(s1) + n + 1;
                if (!realloc(s1, stringSize*sizeof(char)))
                {
                    free(s1);
                    free(s2);
                    printf("Memory allocation failed!");
                    return;
                }
            }
            strncats(s1, s2, n);
            printf("New S1: \"%s\"\n", s1);
            break;

        case 6:
            strreverse(s1);
            printf("Reversed S1: \"%s\"\n", s1);
            break;

        case 7:
            strlower(s1);
            printf("Lowercase S1: \"%s\"\n", s1);
            break;

        case 8:
            strupper(s1);
            printf("Uppercase S1: \"%s\"\n", s1);
            break;

        case 9:
            printf("Enter maximum characters for the new string: ");
            while (scanf("%d", &stringSize) != 1 || stringSize <= 1)
            {
                while (getchar() != '\n');
                printf("Enter maximum character for the string, string size should be greater than 1: ");
            }

            if (!realloc(s1, stringSize * sizeof(char)) || !realloc(s2, stringSize * sizeof(char)))
            {
                free(s1);
                free(s2);
                printf("Memory allocation failed!");
                return;
            }
            printf("Enter new S1: ");
            getstring(s1, stringSize);
            break;

        default:
            printf("Invalid option!\n");
            continue;
        }
    }
}