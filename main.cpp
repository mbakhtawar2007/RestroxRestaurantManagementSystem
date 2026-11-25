// RestroX - Restaurant Management System
// Entry point: loads all saved records, then runs the main menu loop.
#include <iostream>
#include "input.h"
#include "structures.h"
#include "employee.h"
#include "customer.h"
#include "menu.h"
#include "inventory.h"
#include "orders.h"

using namespace std;

// Displays summary counts and total sales for all modules.
void showDashboard() {
    cout << "\n====================================\n";
    cout << "           RESTROX DASHBOARD        \n";
    cout << "====================================\n";
    cout << "Total Employees : " << getEmployeeCount() << '\n';
    cout << "Total Customers : " << getCustomerCount() << '\n';
    cout << "Menu Items      : " << getMenuCount() << '\n';
    cout << "Ingredients     : " << getIngredientCount() << '\n';
    cout << "Total Orders    : " << getOrderCount() << '\n';
    cout << "Total Sales     : Rs. " << getTotalSales() << '\n';
}

// Program entry point: loads saved data, shows the main menu, and routes to each module.
int main() {
    // Load saved records before showing the main menu.
    loadEmployees();
    loadCustomers();
    loadMenuItems();
    loadInventory();
    loadOrders();

    int choice;

    do {
        cout << "\n====================================\n";
        cout << "               RESTROX              \n";
        cout << "       RESTAURANT MANAGEMENT        \n";
        cout << "====================================\n";
        cout << "1. Dashboard\n";
        cout << "2. Employee Management\n";
        cout << "3. Customer Management\n";
        cout << "4. Menu Management\n";
        cout << "5. Inventory Management\n";
        cout << "6. Order Management\n";
        cout << "7. Exit\n";

        choice = readInt("\nEnter your choice: ");

        if (choice == 1) {
            showDashboard();
        } else if (choice == 2) {
            employeeMenu();
        } else if (choice == 3) {
            customerMenu();
        } else if (choice == 4) {
            menuManagement();
        } else if (choice == 5) {
            inventoryMenu();
        } else if (choice == 6) {
            orderMenu();
        } else if (choice == 7) {
            cout << "\nThank you for using RESTROX. Goodbye!\n";
        } else {
            cout << "Invalid choice. Please select a number from 1 to 7.\n";
        }
    } while (choice != 7);

    return 0;
}
