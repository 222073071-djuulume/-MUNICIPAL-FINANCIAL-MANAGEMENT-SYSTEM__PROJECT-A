
#include <stdio.h>
#include <string.h>
#include "assets.h"

static char ids[MAX_ASSETS][15];
static char names[MAX_ASSETS][50];
static char types[MAX_ASSETS][20];
static double values[MAX_ASSETS];
static char depts[MAX_ASSETS][50];
static char conds[MAX_ASSETS][10];
static int count = 0;

static void displayAssetMenu(void)
{
    printf("\n===== ASSET MANAGEMENT =====\n");
    printf("1. Add Asset (e.g. new truck)\n");
    printf("2. Display Assets (e.g. full list)\n");
    printf("3. Search Asset (e.g. A001)\n");
    printf("4. Asset Report (e.g. total value)\n");
    printf("5. Back to Main Menu (e.g. exit)\n");
    printf("Enter your choice: ");
}

static int findAsset(char id[])
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(ids[i], id) == 0)
        {
            return i;
        }
    }
    return -1;
}

void addAsset(void)
{
    char id[15];
    int exists;
    int choice;
    double value;

    if (count >= MAX_ASSETS)
    {
        printf("Asset register is full.\n");
        return;
    }

    printf("\n--- ADD ASSET ---\n");

    do
    {
        printf("Asset ID (e.g. A001): ");
        scanf("%14s", id);
        exists = findAsset(id);
        if (exists != -1)
        {
            printf("Error: Asset ID already exists.\n");
        }
    } while (exists != -1);
    strcpy(ids[count], id);

    printf("Asset name (e.g. Toyota_Hilux): ");
    scanf("%49s", names[count]);

    printf("\nAsset type:\n");
    printf("1. Vehicle (e.g. truck, bus)\n");
    printf("2. Computer (e.g. laptop)\n");
    printf("3. Building (e.g. library)\n");
    printf("4. Equipment (e.g. generator)\n");
    printf("5. Furniture (e.g. desk)\n");
    do
    {
        printf("Select type (1-5): ");
        scanf("%d", &choice);
        if (choice < 1 || choice > 5)
        {
            printf("Invalid choice.\n");
        }
    } while (choice < 1 || choice > 5);

    switch (choice)
    {
    case 1:
        strcpy(types[count], "Vehicle");
        break;
    case 2:
        strcpy(types[count], "Computer");
        break;
    case 3:
        strcpy(types[count], "Building");
        break;
    case 4:
        strcpy(types[count], "Equipment");
        break;
    case 5:
        strcpy(types[count], "Furniture");
        break;
    }

    do
    {
        printf("Purchase value N$ (e.g. 15000): ");
        scanf("%lf", &value);
        if (value <= 0)
        {
            printf("Error: value must be above 0.\n");
        }
    } while (value <= 0);
    values[count] = value;

    printf("Department (e.g. Finance): ");
    scanf("%49s", depts[count]);

    printf("\nCondition:\n");
    printf("1. Good (e.g. works perfectly)\n");
    printf("2. Fair (e.g. minor wear)\n");
    printf("3. Poor (e.g. needs repair)\n");
    do
    {
        printf("Select condition (1-3): ");
        scanf("%d", &choice);
        if (choice < 1 || choice > 3)
        {
            printf("Invalid choice.\n");
        }
    } while (choice < 1 || choice > 3);

    switch (choice)
    {
    case 1:
        strcpy(conds[count], "Good");
        break;
    case 2:
        strcpy(conds[count], "Fair");
        break;
    case 3:
        strcpy(conds[count], "Poor");
        break;
    }

    printf("\nAsset added successfully.\n");
    count++;
}

static void displayAssetCard(int index)
{
    printf("ID         : %s\n", ids[index]);
    printf("Name       : %s\n", names[index]);
    printf("Type       : %s\n", types[index]);
    printf("Value      : N$%.2f\n", values[index]);
    printf("Department : %s\n", depts[index]);
    printf("Condition  : %s\n", conds[index]);
}

void displayAssets(void)
{
    printf("\n--- ASSET REGISTER ---\n");
    if (count == 0)
    {
        printf("No assets registered yet.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        printf("\nAsset %d\n", i + 1);
        printf("-----------------\n");
        displayAssetCard(i);
    }
    printf("\nTotal assets: %d\n", count);
}

void searchAsset(void)
{
    char key[50];
    int choice;
    int found = 0;

    printf("\n--- SEARCH ASSET ---\n");
    if (count == 0)
    {
        printf("No assets registered yet.\n");
        return;
    }

    printf("1. By Asset ID (e.g. A001)\n");
    printf("2. By Asset name (e.g. Laptop)\n");
    do
    {
        printf("Select (1-2): ");
        scanf("%d", &choice);
        if (choice < 1 || choice > 2)
        {
            printf("Invalid choice.\n");
        }
    } while (choice < 1 || choice > 2);

    printf("Enter search text: ");
    scanf("%49s", key);

    for (int i = 0; i < count; i++)
    {
        if ((choice == 1 && strcmp(ids[i], key) == 0) ||
            (choice == 2 && strcmp(names[i], key) == 0))
        {
            printf("\nAsset found:\n");
            printf("-----------------\n");
            displayAssetCard(i);
            found = 1;
        }
    }

    if (found == 0)
    {
        printf("Asset not found.\n");
    }
}

double calculateTotalValue(void)
{
    double total = 0;
    for (int i = 0; i < count; i++)
    {
        total = total + values[i];
    }
    return total;
}

void displayAssetReport(void)
{
    int poorCount = 0;
    int highest = 0;
    double total;

    printf("\n===== ASSET REPORT =====\n");
    if (count == 0)
    {
        printf("No assets registered yet.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if (strcmp(conds[i], "Poor") == 0)
        {
            poorCount++;
        }
        if (values[i] > values[highest])
        {
            highest = i;
        }
    }

    total = calculateTotalValue();
    printf("Total assets : %d\n", count);
    printf("Total value  : N$%.2f\n", total);
    printf("Average value: N$%.2f\n", total / count);
    printf("Most valuable: %s\n", names[highest]);
    printf("  (N$%.2f)\n", values[highest]);
    printf("Poor condition: %d\n", poorCount);

    displayAssets();
}

void assetMenu(void)
{
    int choice;

    do
    {
        displayAssetMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addAsset();
            break;
        case 2:
            displayAssets();
            break;
        case 3:
            searchAsset();
            break;
        case 4:
            displayAssetReport();
            break;
        case 5:
            printf("Returning to main menu...\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 5);
}
