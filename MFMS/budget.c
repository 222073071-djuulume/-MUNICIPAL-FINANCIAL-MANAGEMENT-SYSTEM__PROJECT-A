#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "budget.h"
#include "utils.h"

Budget budgets[MAX_BUDGETS];
int budgetCount = 0;

double calculateRemaining(double allocated, double expenditure)
{
    return allocated - expenditure;
}

int isWithinBudget(double allocated, double expenditure)
{
    return expenditure <= allocated;
}

static int hasLetter(const char *text)
{
    int i;
    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)text[i]))
            return 1;
    }
    return 0;
}

static int findBudget(const char *department)
{
    int i;
    for (i = 0; i < budgetCount; i++)
    {
        if (strcmp(budgets[i].department, department) == 0)
            return i;
    }
    return -1;
}

void addBudget(void)
{
    Budget b;

    if (budgetCount >= MAX_BUDGETS)
    {
        printf("Budget list is full (%d).\n", MAX_BUDGETS);
        return;
    }
    printf("\n--- Add Departmental Budget ---\n");
    do
    {
        readLine("Department: ", b.department, sizeof(b.department));
        if (!hasLetter(b.department))
        {
            printf("  Department name must contain at least one letter.\n");
        }
    } while (!hasLetter(b.department));
    if (findBudget(b.department) != -1)
    {
        printf("A budget for %s already exists.\n", b.department);
        return;
    }
    b.allocated = readDouble("Allocated budget (N$): ", 0.0, 1000000000.0);
    b.expenditure = readDouble("Expenditure so far (N$): ", 0.0, 1000000000.0);

    budgets[budgetCount++] = b;
    printf("Budget saved. Remaining: N$%.2f\n",
           calculateRemaining(b.allocated, b.expenditure));
}

void addExpenditure(void)
{
    char dept[50];
    int i;
    double amount;

    printf("\n--- Record Expenditure ---\n");
    if (budgetCount == 0)
    {
        printf("No budgets yet. Add a budget first.\n");
        return;
    }
    readLine("Department: ", dept, sizeof(dept));
    i = findBudget(dept);
    if (i < 0)
    {
        printf("Department not found.\n");
        return;
    }
    amount = readDouble("Amount spent (N$): ", 0.0, 1000000000.0);
    budgets[i].expenditure += amount;
    printf("Updated. Remaining: N$%.2f (%s)\n",
           calculateRemaining(budgets[i].allocated, budgets[i].expenditure),
           isWithinBudget(budgets[i].allocated, budgets[i].expenditure)
               ? "WITHIN BUDGET"
               : "OVER BUDGET");
}

void displayBudgets(void)
{
    int i;
    double remaining;

    printf("\n--- Budgets ---\n");
    if (budgetCount == 0)
    {
        printf("No budgets captured yet.\n");
        return;
    }
    for (i = 0; i < budgetCount; i++)
    {
        remaining = calculateRemaining(budgets[i].allocated, budgets[i].expenditure);
        printf("\nDepartment:       %s\n", budgets[i].department);
        printf("Allocated Budget: N$%.2f\n", budgets[i].allocated);
        printf("Expenditure:      N$%.2f\n", budgets[i].expenditure);
        printf("Remaining Budget: N$%.2f\n", remaining);
        printf("Status:           %s\n",
               isWithinBudget(budgets[i].allocated, budgets[i].expenditure)
                   ? "WITHIN BUDGET"
                   : "OVER BUDGET");
    }
}

void budgetMenu(void)
{
    int choice;
    do
    {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Add departmental budget\n2. Record expenditure\n");
        printf("3. Display budgets\n4. Back\n");
        choice = readInt("Enter your choice: ", 1, 4);
        switch (choice)
        {
        case 1:
            addBudget();
            break;
        case 2:
            addExpenditure();
            break;
        case 3:
            displayBudgets();
            break;
        default:
            break;
        }
    } while (choice != 4);
}
