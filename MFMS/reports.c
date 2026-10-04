#include <stdio.h>
#include <string.h>
#include "reports.h"
#include "utils.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

/* --- 1. EMPLOYEE REPORT --- */
void generateEmployeeReport(void)
{
    printHeader("EMPLOYEE REPORT");

    /* Overview placeholder aligned with employees.h module specs */
    printf("Total Employees : 0\n");
    printf("Average Salary : N$ 0.00\n");
    printf("Highest Salary : N$ 0.00\n");
    printf("Lowest Salary : N$ 0.00\n");
    printLine('-', 50);
}

/* --- 2. BUDGET REPORT --- */
void generateBudgetReport(void)
{
    printHeader("BUDGET REPORT");

    if (budgetCount == 0)
    {
        printf("No departmental budgets recorded.\n");
        return;
    }

    double totalAllocated = 0.0;
    double totalExpenditure = 0.0;
    int overBudgetCount = 0;

    printf("\n%-20s %-15s %-15s %-15s %-15s\n",
           "Department", "Allocated (N$)", "Spent (N$)", "Remaining (N$)", "Status");
    printLine('-', 80);

    for (int i = 0; i < budgetCount; i++)
    {
        double remaining = calculateRemaining(budgets[i].allocated, budgets[i].expenditure);
        int within = isWithinBudget(budgets[i].allocated, budgets[i].expenditure);

        totalAllocated += budgets[i].allocated;
        totalExpenditure += budgets[i].expenditure;

        if (!within)
        {
            overBudgetCount++;
        }

        printf("%-20s %-15.2f %-15.2f %-15.2f %-15s\n",
               budgets[i].department,
               budgets[i].allocated,
               budgets[i].expenditure,
               remaining,
               within ? "WITHIN BUDGET" : "OVER BUDGET");
    }

    printLine('-', 80);
    printf("Total Allocated Budget : N$ %.2f\n", totalAllocated);
    printf("Total Expenditure : N$ %.2f\n", totalExpenditure);
    printf("Total Remaining Budget : N$ %.2f\n", totalAllocated - totalExpenditure);
    printf("Departments Over Budget: %d\n", overBudgetCount);
    printLine('-', 80);
}

/* --- 3. SUPPLIER REPORT --- */
void generateSupplierReport(void)
{
    printHeader("SUPPLIER REPORT");
    /* Calls supplier display from suppliers.h */
    displaySuppliers();
}

/* --- 4. ASSET REPORT --- */
void generateAssetReport(void)
{
    printHeader("ASSET REPORT");
    printf("No assets recorded yet");
}

/* --- 5. REPORTS MENU --- */
void reportsMenu(void)
{
    int choice;

    do
    {
        printHeader("REPORTS MODULE");
        printf("1. Employee Summary Report\n");
        printf("2. Departmental Budget Report\n");
        printf("3. Supplier Summary Report\n");
        printf("4. Asset Summary Report\n");
        printf("5. Generate All Reports\n");
        printf("6. Back to Main Menu\n");

        choice = readInt("Enter your choice: ", 1, 6);

        switch (choice)
        {
        case 1:
            generateEmployeeReport();
            break;
        case 2:
            generateBudgetReport();
            break;
        case 3:
            generateSupplierReport();
            break;
        case 4:
            generateAssetReport();
            break;
        case 5:
            generateEmployeeReport();
            generateBudgetReport();
            generateSupplierReport();
            generateAssetReport();
            break;
        case 6:
            printf("Returning to main menu...\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 6);
}
