/*
 * employees.c - Employee Management module.
 * TODO (Student 1): store employees in parallel arrays (Week 6) and
 * implement each function below.
 */
#include <stdio.h>
#include "employees.h"
#include "utils.h"

/* TODO: declare your parallel arrays here, e.g.
 * static int    empId[MAX_EMPLOYEES];
 * static char   empName[MAX_EMPLOYEES][EMP_NAME_LEN];
 * static double empBasic[MAX_EMPLOYEES];
 * static int    empCount = 0;
 */

double calculateSalary(double basic, double housing, double transport)
{
    /* TODO: gross = basic + housing + transport (Week 3 Lab 1) */
    return 0.0;
}

int searchEmployee(int id, int ids[], int size)
{
    /* TODO: linear search (Week 6) - return index if found, -1 otherwise */
    return -1;
}

void addEmployee(void)
{
    /* TODO: use readInt()/readNonEmpty()/readDouble() from utils.c to
     * capture ID, name, basic, housing, transport; store in the arrays. */
    printf("addEmployee() not implemented yet.\n");
}

void displayEmployees(void)
{
    /* TODO: loop over the arrays and print each employee. */
    printf("displayEmployees() not implemented yet.\n");
}

void employeeMenu(void)
{
    int choice;

    do
    {
        printHeader("EMPLOYEE MANAGEMENT");
        printf("1. Add employee\n");
        printf("2. Display all employees\n");
        printf("3. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 3);

        switch (choice)
        {
            case 1: addEmployee();      break;
            case 2: displayEmployees(); break;
            case 3: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 3);
}
