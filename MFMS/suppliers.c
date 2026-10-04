#include <stdio.h>
#include <string.h>
#include "suppliers.h"

// Parallel arrays storing supplier details
char supplierIDs[MAX_SUPPLIERS][STR_LEN];
char supplierNames[MAX_SUPPLIERS][STR_LEN];
char emails[MAX_SUPPLIERS][STR_LEN];
char phones[MAX_SUPPLIERS][STR_LEN];
char towns[MAX_SUPPLIERS][STR_LEN];

int supplierCount = 0;

static void removeNewline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

static void getString(const char *prompt, char *target)
{
    printf("%s", prompt);
    fgets(target, STR_LEN, stdin);
    removeNewline(target);
}

// Add a new supplier record
void addSupplier(void)
{
    if (supplierCount >= MAX_SUPPLIERS)
    {
        printf("\n[Error] Supplier list is full.\n");
        return;
    }

    printf("\n--- Add New Supplier ---\n");

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    getString("Enter Supplier ID: ", supplierIDs[supplierCount]);
    getString("Enter Supplier Name: ", supplierNames[supplierCount]);
    getString("Enter Email: ", emails[supplierCount]);
    getString("Enter Phone Number: ", phones[supplierCount]);
    getString("Enter Town/Location: ", towns[supplierCount]);

    supplierCount++;
    printf("-> Supplier added successfully!\n");
}

// Display all registered suppliers
void displaySuppliers(void)
{
    if (supplierCount == 0)
    {
        printf("\nNo suppliers registered yet.\n");
        return;
    }

    printf("\n================================ SUPPLIER LIST ================================\n");
    printf("%-10s %-25s %-25s %-15s %-15s\n", "ID", "Name", "Email", "Phone", "Town");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < supplierCount; i++)
    {
        printf("%-10s %-25s %-25s %-15s %-15s\n",
               supplierIDs[i], supplierNames[i], emails[i], phones[i], towns[i]);
    }
    printf("-------------------------------------------------------------------------------\n");
    printf("Total Suppliers: %d\n", supplierCount);
}

// Search for a supplier by ID or Name
void searchSupplier(void)
{
    if (supplierCount == 0)
    {
        printf("\nNo suppliers available to search.\n");
        return;
    }

    char query[STR_LEN];
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    getString("\nEnter Supplier ID or Name to search: ", query);

    int found = 0;
    for (int i = 0; i < supplierCount; i++)
    {
        if (strcmp(supplierIDs[i], query) == 0 || strcmp(supplierNames[i], query) == 0)
        {
            printf("\n--- Supplier Found ---\n");
            printf("ID   : %s\n", supplierIDs[i]);
            printf("Name : %s\n", supplierNames[i]);
            printf("Email: %s\n", emails[i]);
            printf("Phone: %s\n", phones[i]);
            printf("Town : %s\n", towns[i]);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("-> No matching supplier found for \"%s\".\n", query);
    }
}

// Filter and display suppliers matching a specific town
void compareSuppliersByTown(void)
{
    if (supplierCount == 0)
    {
        printf("\nNo suppliers available.\n");
        return;
    }

    char targetTown[STR_LEN];
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    getString("\nEnter Town/Location to filter: ", targetTown);

    int matchCount = 0;
    printf("\n--- Suppliers in %s ---\n", targetTown);

    for (int i = 0; i < supplierCount; i++)
    {
        if (strcmp(towns[i], targetTown) == 0)
        {
            printf("[%d] ID: %-8s | Name: %-20s | Phone: %s\n",
                   matchCount + 1, supplierIDs[i], supplierNames[i], phones[i]);
            matchCount++;
        }
    }

    if (matchCount == 0)
    {
        printf("No suppliers located in %s.\n", targetTown);
    }
}

// Menu interface
void supplierMenu(void)
{
    int choice = 0;

    while (choice != 5)
    {
        printf("\n===========================\n");
        printf("   SUPPLIER MANAGEMENT\n");
        printf("===========================\n");
        printf("1. Add Supplier\n");
        printf("2. Display All Suppliers\n");
        printf("3. Search Supplier (ID/Name)\n");
        printf("4. Filter Suppliers by Town\n");
        printf("5. Exit\n");
        printf("Select Choice: ");

        if (scanf("%d", &choice) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            printf("Invalid input. Enter a number between 1 and 5.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            addSupplier();
            break;
        case 2:
            displaySuppliers();
            break;
        case 3:
            searchSupplier();
            break;
        case 4:
            compareSuppliersByTown();
            break;
        case 5:
            printf("Exiting Supplier Management...\n");
            break;
        default:
            printf("Invalid choice. Select between 1 and 5.\n");
        }
    }
}