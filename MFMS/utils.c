/*
 * utils.c - Shared helper functions.
 * These are implemented so the demo runs; every other module still has
 * its own TODOs to fill in (add/display/search).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

/* Reads one line of text into buffer using fgets(), removes the newline.
 * Returns 1 if the whole line fit in the buffer, 0 if it was too long. */
int readLine(const char prompt[], char buffer[], int size)
{
    size_t length;
    int complete = 1;
    int ch;

    printf("%s", prompt);
    if (fgets(buffer, size, stdin) == NULL)
    {
        printf("\nInput ended. Exiting the system.\n");
        exit(0);
    }

    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
    }
    else
    {
        complete = 0;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            /* discard the rest of a too-long line */
        }
    }
    return complete;
}

/* Keeps asking until the user types something that isn't empty. */
void readNonEmpty(const char prompt[], char buffer[], int size)
{
    while (1)
    {
        if (!readLine(prompt, buffer, size))
        {
            printf("Error: input too long (maximum %d characters).\n", size - 1);
        }
        else if (strlen(buffer) == 0)
        {
            printf("Error: this field cannot be empty.\n");
        }
        else
        {
            return;
        }
    }
}

/* Reads a whole number between min and max (inclusive), re-prompting on
 * anything invalid (Week 3-4 common errors). */
int readInt(const char prompt[], int min, int max)
{
    char buffer[INPUT_SIZE];
    char *end;
    long value;

    while (1)
    {
        if (!readLine(prompt, buffer, INPUT_SIZE) || strlen(buffer) == 0)
        {
            printf("Error: please enter a whole number.\n");
            continue;
        }

        value = strtol(buffer, &end, 10);
        if (*end != '\0')
        {
            printf("Error: '%s' is not a valid whole number.\n", buffer);
        }
        else if (value < min || value > max)
        {
            printf("Error: enter a value between %d and %d.\n", min, max);
        }
        else
        {
            return (int)value;
        }
    }
}

/* Reads a decimal number between min and max (inclusive). */
double readDouble(const char prompt[], double min, double max)
{
    char buffer[INPUT_SIZE];
    char *end;
    double value;

    while (1)
    {
        if (!readLine(prompt, buffer, INPUT_SIZE) || strlen(buffer) == 0)
        {
            printf("Error: please enter a number.\n");
            continue;
        }

        value = strtod(buffer, &end);
        if (*end != '\0')
        {
            printf("Error: '%s' is not a valid number.\n", buffer);
        }
        else if (value < min || value > max)
        {
            printf("Error: enter an amount between %.2f and %.2f.\n", min, max);
        }
        else
        {
            return value;
        }
    }
}

/* Case-insensitive string comparison, built on strcmp() (Week 7). */
int sameText(const char a[], const char b[])
{
    char lowerA[256];
    char lowerB[256];
    int i;

    if (strlen(a) >= sizeof(lowerA) || strlen(b) >= sizeof(lowerB))
    {
        return 0;
    }
    strcpy(lowerA, a);
    strcpy(lowerB, b);
    for (i = 0; lowerA[i] != '\0'; i++) lowerA[i] = (char)tolower((unsigned char)lowerA[i]);
    for (i = 0; lowerB[i] != '\0'; i++) lowerB[i] = (char)tolower((unsigned char)lowerB[i]);

    return strcmp(lowerA, lowerB) == 0;
}

/* VAT at 15% (Week 8). */
double calculateVAT(double amount)
{
    return amount * VAT_RATE;
}

void printLine(char ch, int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        putchar(ch);
    }
    putchar('\n');
}

void printHeader(const char title[])
{
    printf("\n");
    printLine('=', 50);
    printf(" %s\n", title);
    printLine('=', 50);
}
