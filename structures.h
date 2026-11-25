// Shared record definitions used by every module of RestroX.

#ifndef STRUCTURES_H
#define STRUCTURES_H

// One employee: unique ID, name, job role, and monthly salary.
struct Employee {
    int id;
    char name[50];
    char role[30];
    float salary;
};

// One customer: auto-generated ID, name, and phone number.
struct Customer {
    int id;
    char name[50];
    char phone[20];
};

// One food item on the menu: unique ID, name, category, and price.
struct MenuItem {
    int id;
    char name[50];
    char category[30];
    float price;
};


// One stock ingredient: unique ID, name, quantity, and unit (kg, liter, pieces).
struct Ingredient {
    int id;
    char name[50];
    float quantity;
    char unit[20];
};

// One line in an order: the menu item, its name, quantity, and unit price.
struct OrderItem {
    int menuItemID;
    char itemName[50];
    int quantity;
    float price;
};

// One customer order: order ID, customer ID, up to 20 items, and the total bill.
struct Order {
    int orderID;
    int customerID;
    int itemCount;
    OrderItem items[20];
    float total;
};
#endif
