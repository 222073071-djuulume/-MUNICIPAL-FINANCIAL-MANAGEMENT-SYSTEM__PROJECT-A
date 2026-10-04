/*
 * utils.h - Shared helper functions used by every module.
 * Owner: Student 6 (Functions, integration and validation)
 */
#ifndef UTILS_H
#define UTILS_H

#define INPUT_SIZE  128
#define VAT_RATE    0.15

/* ---------- Input (TODO: implement in utils.c) ---------- */
int    readLine(const char prompt[], char buffer[], int size);
void   readNonEmpty(const char prompt[], char buffer[], int size);
int    readInt(const char prompt[], int min, int max);
double readDouble(const char prompt[], double min, double max);

/* ---------- Strings ---------- */
int    sameText(const char a[], const char b[]);   /* case-insensitive compare */

/* ---------- Calculations ---------- */
double calculateVAT(double amount);

/* ---------- Output ---------- */
void   printLine(char ch, int count);
void   printHeader(const char title[]);

#endif
