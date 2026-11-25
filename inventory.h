// Inventory module interface.
#ifndef INVENTORY_H
#define INVENTORY_H

// Loads saved ingredients into memory.
void loadInventory();
// Saves all ingredients to file; returns false if the file cannot be opened.
bool saveInventory();
// Returns the number of ingredients currently in memory.
int getIngredientCount();

// Runs the Inventory Management submenu.
void inventoryMenu();
// Adds one ingredient after validating the ID and quantity.
void addIngredient();
// Prints all ingredients in a formatted table.
void viewInventory();

#endif
