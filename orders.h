// Order module interface.
#ifndef ORDERS_H
#define ORDERS_H

// Loads saved orders into memory.
void loadOrders();
// Saves all orders to file; returns false if the file cannot be opened.
bool saveOrders();
// Returns the number of orders currently in memory.
int getOrderCount();
// Returns total sales (the sum of all order totals).
float getTotalSales();

// Runs the Order Management submenu.
void orderMenu();
// Creates one order and prints its bill.
void createOrder();
// Prints every order with its items and total.
void viewOrders();

#endif
