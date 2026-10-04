/*
 * assets.c - Asset Management module.
 * TODO (Student 4): store asset ID, name, type, value, department and
 * condition in parallel arrays, and implement each function.
 */
#include <stdio.h>
#include "assets.h"
#include "utils.h"

/* TODO: declare your parallel arrays here. */

void addAsset(void)
{
    /* TODO: capture asset ID, name, type, value, department, condition. */
    printf("addAsset() not implemented yet.\n");
}

void displayAssets(void)
{
    /* TODO: loop over assets and print each one. */
    printf("displayAssets() not implemented yet.\n");
}

void searchAsset(void)
{
    /* TODO: search by ID or name. */
    printf("searchAsset() not implemented yet.\n");
}

void assetMenu(void)
{
    int choice;

    do
    {
        printHeader("ASSET MANAGEMENT");
        printf("1. Add asset\n");
        printf("2. Display assets\n");
        printf("3. Search asset\n");
        printf("4. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 4);

        switch (choice)
        {
            case 1: addAsset();      break;
            case 2: displayAssets(); break;
            case 3: searchAsset();   break;
            case 4: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}
