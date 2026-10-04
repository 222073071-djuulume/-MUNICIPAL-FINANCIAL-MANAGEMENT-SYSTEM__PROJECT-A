#ifndef BUDGET_H
#define BUDGET_H

#define MAX_BUDGETS 30

typedef struct
{
    char department[50];
    double allocated;
    double expenditure;
} Budget;

extern Budget budgets[MAX_BUDGETS];
extern int budgetCount;

void budgetMenu(void);
void addBudget(void);
void addExpenditure(void);
void displayBudgets(void);
double calculateRemaining(double allocated, double expenditure);
int isWithinBudget(double allocated, double expenditure);

#endif
