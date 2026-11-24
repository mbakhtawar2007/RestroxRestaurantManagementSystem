#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "structures.h"

void loadCustomers();
bool saveCustomers();
int getCustomerCount();

void customerMenu();
void addCustomer();
void viewCustomers();
int findOrAddCustomer(const char* name);

#endif
