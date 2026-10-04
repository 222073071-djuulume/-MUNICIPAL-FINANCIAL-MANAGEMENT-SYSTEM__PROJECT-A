/*
 * reports.c - Reports module.
 * TODO (Student 5): once the other modules expose "get" functions for
 * their data (e.g. getEmployeeCount(), getEmployeeGross(i)), use them
 * here to calculate totals, averages, highest and lowest (Week 5).
 */
#include <stdio.h>
#include "reports.h"
#include "utils.h"

void employeeReport(void)
{
    /* TODO */
    printf("employeeReport() not implemented yet.\n");
}

void budgetReport(void)
{
    /* TODO */
    printf("budgetReport() not implemented yet.\n");
}

void supplierReport(void)
{
    /* TODO */
    printf("supplierReport() not implemented yet.\n");
}

void assetReport(void)
{
    /* TODO */
    printf("assetReport() not implemented yet.\n");
}

void reportsMenu(void)
{
    int choice;

    do
    {
        printHeader("REPORTS");
        printf("1. Employee report\n");
        printf("2. Budget report\n");
        printf("3. Supplier report\n");
        printf("4. Asset report\n");
        printf("5. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice)
        {
            case 1: employeeReport(); break;
            case 2: budgetReport();   break;
            case 3: supplierReport(); break;
            case 4: assetReport();    break;
            case 5: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
}
