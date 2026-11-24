
#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Employee {
    int id;
    char name[50];
    char role[30];
    float salary;
};

struct Customer {
    int id;
    char name[50];
    char phone[20];
};

struct MenuItem {
    int id;
    char name[50];
    char category[30];
    float price;
};


struct Ingredient {
    int id;
    char name[50];
    float quantity;
    char unit[20];
};

struct OrderItem {
    int menuItemID;
    char itemName[50];
    int quantity;
    float price;
};

struct Order {
    int orderID;
    int customerID;
    int itemCount;
    OrderItem items[20];
    float total;
};
#endif
