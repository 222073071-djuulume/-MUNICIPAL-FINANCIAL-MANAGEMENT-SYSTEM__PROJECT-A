/*
 * suppliers.c - Supplier Management module.
 * TODO (Student 3): store supplier name, email, phone, town in parallel
 * character arrays (Week 7) and implement each function using
 * strlen(), strcmp(), strcpy(), strcat() where appropriate.
 */
#include <stdio.h>
#include <string.h>
#include "suppliers.h"
#include "utils.h"

/* TODO: declare your parallel arrays here, e.g.
 * static char supName[MAX_SUPPLIERS][SUP_NAME_LEN];
 * static char supEmail[MAX_SUPPLIERS][60];
 * static char supPhone[MAX_SUPPLIERS][20];
 * static char supTown[MAX_SUPPLIERS][40];
 * static int  supCount = 0;
 */

void addSupplier(void)
{
    /* TODO: capture name, email, phone, town with readNonEmpty(). */
    printf("addSupplier() not implemented yet.\n");
}

void displaySuppliers(void)
{
    /* TODO: loop over suppliers and print each one. */
    printf("displaySuppliers() not implemented yet.\n");
}

void searchSupplier(void)
{
    /* TODO: use strcmp() (or sameText() from utils.c) to find a
     * supplier by name. */
    printf("searchSupplier() not implemented yet.\n");
}

void supplierMenu(void)
{
    int choice;

    do
    {
        printHeader("SUPPLIER MANAGEMENT");
        printf("1. Add supplier\n");
        printf("2. Display suppliers\n");
        printf("3. Search supplier\n");
        printf("4. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 4);

        switch (choice)
        {
            case 1: addSupplier();      break;
            case 2: displaySuppliers(); break;
            case 3: searchSupplier();   break;
            case 4: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}
