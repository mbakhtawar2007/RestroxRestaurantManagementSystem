#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "customer.h"
#include "structures.h"
#include "input.h"

using namespace std;

const int MAX_CUSTOMERS = 100;
Customer customers[MAX_CUSTOMERS];
int customerCount = 0;

void loadCustomers() {
    ifstream file("data/customers.txt");

    if (!file) {
        return;
    }

    customerCount = 0;

    while (customerCount < MAX_CUSTOMERS) {
        Customer customer;

        if (!(file >> customer.id)) break;
        file.ignore(10000, '\n');

        if (!file.getline(customer.name, 50)) break;
        if (!file.getline(customer.phone, 20)) break;

        if (customer.id <= 0) {
            continue;
        }

        customers[customerCount] = customer;
        customerCount++;
    }

    file.close();
}

bool saveCustomers() {
    ofstream file("data/customers.txt");

    if (!file) {
        return false;
    }

    for (int i = 0; i < customerCount; i++) {
        file << customers[i].id << '\n';
        file << customers[i].name << '\n';
        file << customers[i].phone << '\n';
    }

    file.close();
    return !file.fail();
}

int getCustomerCount() {
    return customerCount;
}

// Customer IDs start at 1001 and increase automatically.
int generateCustomerID() {
    int highestID = 1000;

    for (int i = 0; i < customerCount; i++) {
        if (customers[i].id > highestID) {
            highestID = customers[i].id;
        }
    }

    return highestID + 1;
}

int findOrAddCustomer(const char* name) {
    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].name, name) == 0) {
            cout << "\nExisting customer found. Customer ID: "
                 << customers[i].id << '\n';
            return customers[i].id;
        }
    }

    if (customerCount >= MAX_CUSTOMERS) {
        cout << "Customer storage is full.\n";
        return -1;
    }

    Customer newCustomer;
    newCustomer.id = generateCustomerID();
    strcpy(newCustomer.name, name);

    cout << "\nNew customer detected.\n";
    readText("Enter Phone Number: ", newCustomer.phone, 20);

    customers[customerCount] = newCustomer;
    customerCount++;

    if (saveCustomers()) {
        cout << "Customer registered and saved successfully.\n";
    } else {
        cout << "Customer registered in memory, but the file could not be saved.\n";
    }

    cout << "Generated Customer ID: " << newCustomer.id << '\n';
    return newCustomer.id;
}

void addCustomer() {
    cout << "\n========== ADD CUSTOMER ==========\n";

    char name[50];
    readText("Enter Customer Name: ", name, 50);

    findOrAddCustomer(name);
}

void viewCustomers() {
    cout << "\n========== CUSTOMER RECORDS ==========\n";

    if (customerCount == 0) {
        cout << "No customers registered yet.\n";
        return;
    }

    cout << left << setw(10) << "ID"
         << setw(25) << "NAME"
         << "PHONE\n";
    cout << "------------------------------------------------\n";

    for (int i = 0; i < customerCount; i++) {
        cout << left << setw(10) << customers[i].id
             << setw(25) << customers[i].name
             << customers[i].phone << '\n';
    }
}

void customerMenu() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "         CUSTOMER MANAGEMENT        \n";
        cout << "====================================\n";
        cout << "1. Add Customer\n";
        cout << "2. View Customers\n";
        cout << "3. Back to Main Menu\n";

        choice = readInt("\nEnter your choice: ");

        if (choice == 1) {
            addCustomer();
        } else if (choice == 2) {
            viewCustomers();
        } else if (choice == 3) {
            cout << "Returning to Main Menu...\n";
        } else {
            cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    } while (choice != 3);
}
