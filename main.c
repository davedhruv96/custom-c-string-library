#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"


int main()
{
    DynamicString *s1 = createString(5);
    DynamicString *s2 = createString(5); 
    char *temp1, *temp2;
    size_t n;
    int menu;

    printf("\n--- Welcome to the Custom C String Library ---\n");
    printf("Please enter the first string to start: ");
    getstring(s1);

    while (1)
    {
        printf("\n\n----------------------------------------\n");
        printf("Current String 1: \"%s\"\n", s1->data);
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
        int scanCheck = scanf("%d", &menu);
        while (scanCheck != 1) // checking if a number is entered or not
        {
            while (getchar() != '\n');
            printf("Menu num is between 0 and 9, reEnter menu: ");
            scanCheck = scanf("%d", &menu);
        }
        switch (menu)
        {
        case 0:
            destroyString(s1);
            destroyString(s2);
            printf("Exiting...\n");
            return 0;

        case 1:
            printf("Length of S1: %zu\n", strlength(s1->data));
            break;

        case 2:
            strcopy(s1, s2);
            printf("Copied! S2 is now: \"%s\"\n", s2->data);
            break;

        case 3:
            printf("Enter S2 to compare: ");
            getstring(s2);
            if (strcompare(s1->data, s2->data))
            {
                printf("S2: \"%s\"\n", s2->data);
                printf("Result: The strings are IDENTICAL.\n");
            }
            else
            {
                printf("S2: \"%s\"\n", s2->data);
                printf("Result: The strings are DIFFERENT.\n");
            }
            break;

        case 4:
            printf("Enter string to append to S1: ");
            if (getstring(s2) != 0)
            {
                printf("Memory allocation failed!\n");
            }
            strcats(s1, s2);
            printf("New S1: \"%s\"\n", s1->data);
            break;

        case 5:
            printf("Enter string to append: ");
            getstring(s2);
            printf("How many characters? ");
            while (scanf("%zu", &n) != 1 || (signed)n <= 0) 
            {
                while (getchar() != '\n');
                printf("The number of characters to be appended should be a positive integer: ");
            }
            strncats(s1, s2, n);
            printf("New S1: \"%s\"\n", s1->data);
            break;

        case 6:
            strreverse(s1->data);
            printf("Reversed S1: \"%s\"\n", s1->data);
            break;

        case 7:
            strlower(s1->data);
            printf("Lowercase S1: \"%s\"\n", s1->data);
            break;

        case 8:
            strupper(s1->data);
            printf("Uppercase S1: \"%s\"\n", s1->data);
            break;

        case 9:
            printf("Enter new S1: ");
            getstring(s1);
            break;

        default:
            printf("Invalid option!\n");
            continue;
        }
    }
    return 0;
}