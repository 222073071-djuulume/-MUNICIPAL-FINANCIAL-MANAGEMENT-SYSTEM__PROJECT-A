#include <stdio.h>
#include "utils.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

void displayWelcome(void);
void displayMenu(void);

void displayWelcome(void)
{
    printf("\nWelcome to the Municipal Financial Management System\n");
}

void displayMenu(void)
{
    printf("\n");
    printLine('=', 40);
    printf("MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printLine('=', 40);
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
}

int main(void)
{
    int choice;

    displayWelcome();

    do
    {
        displayMenu();
        choice = readInt("Enter your choice: ", 1, 6);

        switch (choice)
        {
        case 1:
            employeeMenu();
            break;
        case 2:
            budgetMenu();
            break;
        case 3:
            supplierMenu();
            break;
        case 4:
            assetMenu();
            break;
        case 5:
            reportsMenu();
            break;
        case 6:
            printf("\nGoodbye.\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 6);

    return 0;
}