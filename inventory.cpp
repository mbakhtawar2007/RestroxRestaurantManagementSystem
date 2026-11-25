// Inventory management: load, save, add, and view stock ingredients.
#include <iostream>
#include <fstream>
#include <iomanip>
#include "inventory.h"
#include "structures.h"
#include "input.h"

using namespace std;

const int MAX_INGREDIENTS = 100;
Ingredient ingredients[MAX_INGREDIENTS];
int ingredientCount = 0;

// Loads ingredients from data/inventory.txt; skips invalid rows.
void loadInventory() {
    ifstream file("data/inventory.txt");

    if (!file) {
        return;
    }

    ingredientCount = 0;

    while (ingredientCount < MAX_INGREDIENTS) {
        Ingredient ingredient;

        if (!(file >> ingredient.id)) break;
        file.ignore(10000, '\n');

        if (!file.getline(ingredient.name, 50)) break;
        if (!(file >> ingredient.quantity)) break;
        file.ignore(10000, '\n');
        if (!file.getline(ingredient.unit, 20)) break;

        if (ingredient.id <= 0 || ingredient.quantity < 0) {
            continue;
        }

        ingredients[ingredientCount] = ingredient;
        ingredientCount++;
    }

    file.close();
}

// Rewrites data/inventory.txt from memory; returns false if the file cannot be opened.
bool saveInventory() {
    ofstream file("data/inventory.txt");

    if (!file) {
        return false;
    }

    for (int i = 0; i < ingredientCount; i++) {
        file << ingredients[i].id << '\n';
        file << ingredients[i].name << '\n';
        file << ingredients[i].quantity << '\n';
        file << ingredients[i].unit << '\n';
    }

    file.close();
    return !file.fail();
}

// Returns the number of ingredients currently in memory.
int getIngredientCount() {
    return ingredientCount;
}

// Adds one ingredient after checking for a duplicate ID and a negative quantity.
void addIngredient() {
    cout << "\n========== ADD INGREDIENT ==========\n";

    if (ingredientCount >= MAX_INGREDIENTS) {
        cout << "Inventory storage is full.\n";
        return;
    }

    Ingredient newIngredient;
    newIngredient.id = readInt("Enter Ingredient ID: ");

    if (newIngredient.id <= 0) {
        cout << "Ingredient ID must be greater than zero.\n";
        return;
    }

    for (int i = 0; i < ingredientCount; i++) {
        if (ingredients[i].id == newIngredient.id) {
            cout << "This ingredient ID already exists.\n";
            return;
        }
    }

    readText("Enter Ingredient Name: ", newIngredient.name, 50);
    newIngredient.quantity = readFloat("Enter Quantity: ");

    if (newIngredient.quantity < 0) {
        cout << "Quantity cannot be negative. Ingredient was not added.\n";
        return;
    }

    readText("Enter Unit (kg/liter/pieces): ", newIngredient.unit, 20);

    ingredients[ingredientCount] = newIngredient;
    ingredientCount++;

    if (saveInventory()) {
        cout << "Ingredient added and saved successfully.\n";
    } else {
        cout << "Ingredient added in memory, but the file could not be saved.\n";
    }
}

// Prints all ingredients in a formatted table.
void viewInventory() {
    cout << "\n========== INVENTORY RECORDS ==========\n";

    if (ingredientCount == 0) {
        cout << "No ingredients registered yet.\n";
        return;
    }

    cout << left << setw(10) << "ID"
         << setw(25) << "NAME"
         << setw(15) << "QUANTITY"
         << "UNIT\n";
    cout << "------------------------------------------------------\n";

    for (int i = 0; i < ingredientCount; i++) {
        cout << left << setw(10) << ingredients[i].id
             << setw(25) << ingredients[i].name
             << setw(15) << ingredients[i].quantity
             << ingredients[i].unit << '\n';
    }
}

// Runs the Inventory Management submenu until the user goes back.
void inventoryMenu() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "         INVENTORY MANAGEMENT       \n";
        cout << "====================================\n";
        cout << "1. Add Ingredient\n";
        cout << "2. View Inventory\n";
        cout << "3. Back to Main Menu\n";

        choice = readInt("\nEnter your choice: ");

        if (choice == 1) {
            addIngredient();
        } else if (choice == 2) {
            viewInventory();
        } else if (choice == 3) {
            cout << "Returning to Main Menu...\n";
        } else {
            cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    } while (choice != 3);
}
