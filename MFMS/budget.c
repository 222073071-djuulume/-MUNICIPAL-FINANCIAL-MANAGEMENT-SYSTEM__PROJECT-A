/*
 * budget.c - Budget Management module.
 * TODO (Student 2): store department name, allocated budget and
 * expenditure in parallel arrays, and implement each function.
 */
#include <stdio.h>
#include "budget.h"
#include "utils.h"

/* TODO: declare your parallel arrays here. */

double calculateBudget(double revenue, double expenditure)
{
    /* TODO: revenue - expenditure (Week 8 Lab Task 4) */
    return 0.0;
}

void addDepartmentBudget(void)
{
    /* TODO: capture department name and allocated budget. */
    printf("addDepartmentBudget() not implemented yet.\n");
}

void displayBudgets(void)
{
    /* TODO: loop over departments; use calculateBudget() to get the
     * remaining amount and print WITHIN BUDGET or OVER BUDGET. */
    printf("displayBudgets() not implemented yet.\n");
}

void budgetMenu(void)
{
    int choice;

    do
    {
        printHeader("BUDGET MANAGEMENT");
        printf("1. Add department budget\n");
        printf("2. Display budgets\n");
        printf("3. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 3);

        switch (choice)
        {
            case 1: addDepartmentBudget(); break;
            case 2: displayBudgets();      break;
            case 3: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 3);
}
