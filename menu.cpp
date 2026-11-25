// Menu management: load, save, add, view, and look up food items.
#include <iostream>
#include <fstream>
#include <iomanip>
#include "menu.h"
#include "structures.h"
#include "input.h"

using namespace std;

const int MAX_MENU_ITEMS = 100;
MenuItem menuItems[MAX_MENU_ITEMS];
int menuCount = 0;

// Loads menu items from data/menu.txt; skips invalid rows.
void loadMenuItems() {
    ifstream file("data/menu.txt");

    if (!file) {
        return;
    }

    menuCount = 0;

    while (menuCount < MAX_MENU_ITEMS) {
        MenuItem item;

        if (!(file >> item.id)) break;
        file.ignore(10000, '\n');

        if (!file.getline(item.name, 50)) break;
        if (!file.getline(item.category, 30)) break;
        if (!(file >> item.price)) break;
        file.ignore(10000, '\n');

        if (item.id <= 0 || item.price < 0) {
            continue;
        }

        menuItems[menuCount] = item;
        menuCount++;
    }

    file.close();
}

// Rewrites data/menu.txt from memory; returns false if the file cannot be opened.
bool saveMenuItems() {
    ofstream file("data/menu.txt");

    if (!file) {
        return false;
    }

    for (int i = 0; i < menuCount; i++) {
        file << menuItems[i].id << '\n';
        file << menuItems[i].name << '\n';
        file << menuItems[i].category << '\n';
        file << menuItems[i].price << '\n';
    }

    file.close();
    return !file.fail();
}

// Returns the number of menu items currently in memory.
int getMenuCount() {
    return menuCount;
}

// Adds one menu item after checking for a duplicate ID and a negative price.
void addMenuItem() {
    cout << "\n========== ADD MENU ITEM ==========\n";

    if (menuCount >= MAX_MENU_ITEMS) {
        cout << "Menu storage is full.\n";
        return;
    }

    MenuItem newItem;
    newItem.id = readInt("Enter Item ID: ");

    if (newItem.id <= 0) {
        cout << "Item ID must be greater than zero.\n";
        return;
    }

    for (int i = 0; i < menuCount; i++) {
        if (menuItems[i].id == newItem.id) {
            cout << "This item ID already exists.\n";
            return;
        }
    }

    readText("Enter Food Name: ", newItem.name, 50);
    readText("Enter Category: ", newItem.category, 30);
    newItem.price = readFloat("Enter Price: ");

    if (newItem.price < 0) {
        cout << "Price cannot be negative. Menu item was not added.\n";
        return;
    }

    menuItems[menuCount] = newItem;
    menuCount++;

    if (saveMenuItems()) {
        cout << "Menu item added and saved successfully.\n";
    } else {
        cout << "Menu item added in memory, but the file could not be saved.\n";
    }
}

// Prints the full menu in a formatted table.
void viewMenu() {
    cout << "\n========== RESTAURANT MENU ==========\n";

    if (menuCount == 0) {
        cout << "No menu items available. Please add food items first.\n";
        return;
    }

    cout << left << setw(10) << "ID"
         << setw(25) << "FOOD NAME"
         << setw(20) << "CATEGORY"
         << "PRICE\n";
    cout << "---------------------------------------------------------------\n";

    for (int i = 0; i < menuCount; i++) {
        cout << left << setw(10) << menuItems[i].id
             << setw(25) << menuItems[i].name
             << setw(20) << menuItems[i].category
             << menuItems[i].price << '\n';
    }
}

// Finds a menu item by ID; returns true and fills item when found.
bool findMenuItemByID(int id, MenuItem &item) {
    for (int i = 0; i < menuCount; i++) {
        if (menuItems[i].id == id) {
            item = menuItems[i];
            return true;
        }
    }

    return false;
}

// Runs the Menu Management submenu until the user goes back.
void menuManagement() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "           MENU MANAGEMENT          \n";
        cout << "====================================\n";
        cout << "1. Add Food Item\n";
        cout << "2. View Menu\n";
        cout << "3. Back to Main Menu\n";

        choice = readInt("\nEnter your choice: ");

        if (choice == 1) {
            addMenuItem();
        } else if (choice == 2) {
            viewMenu();
        } else if (choice == 3) {
            cout << "Returning to Main Menu...\n";
        } else {
            cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    } while (choice != 3);
}
