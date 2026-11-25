// Customer module interface.
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "structures.h"

// Loads saved customer records into memory.
void loadCustomers();
// Saves all customers to file; returns false if the file cannot be opened.
bool saveCustomers();
// Returns the number of customers currently in memory.
int getCustomerCount();

// Runs the Customer Management submenu.
void customerMenu();
// Adds one customer; the ID is generated automatically.
void addCustomer();
// Prints all customers in a formatted table.
void viewCustomers();
// Returns the ID of the named customer, or registers a new one and returns its ID.
int findOrAddCustomer(const char* name);

#endif
