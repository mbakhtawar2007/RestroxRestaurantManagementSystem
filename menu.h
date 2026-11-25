// Menu module interface.
#ifndef MENU_H
#define MENU_H

#include "structures.h"

// Loads saved menu items into memory.
void loadMenuItems();
// Saves all menu items to file; returns false if the file cannot be opened.
bool saveMenuItems();
// Returns the number of menu items currently in memory.
int getMenuCount();

// Runs the Menu Management submenu.
void menuManagement();
// Adds one menu item after validating the ID and price.
void addMenuItem();
// Prints the full menu in a formatted table.
void viewMenu();
// Finds a menu item by ID; returns true and fills item when found.
bool findMenuItemByID(int id, MenuItem &item);

#endif
