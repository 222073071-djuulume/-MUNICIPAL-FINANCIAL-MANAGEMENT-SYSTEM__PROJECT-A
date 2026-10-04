#ifndef UTILS_H
#define UTILS_H

#define INPUT_SIZE 128
#define VAT_RATE 0.15

int readLine(const char prompt[], char buffer[], int size);
void readNonEmpty(const char prompt[], char buffer[], int size);
int readInt(const char prompt[], int min, int max);
double readDouble(const char prompt[], double min, double max);

int sameText(const char a[], const char b[]);

double calculateVAT(double amount);

void printLine(char ch, int count);
void printHeader(const char title[]);

#endif
