#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "orders.h"
#include "structures.h"
#include "customer.h"
#include "menu.h"
#include "input.h"

using namespace std;

const int MAX_ORDERS = 100;
const int MAX_ITEMS_PER_ORDER = 20;
Order orders[MAX_ORDERS];
int orderCount = 0;

void loadOrders() {
    ifstream file("data/orders.txt");

    if (!file) {
        return;
    }

    orderCount = 0;

    while (orderCount < MAX_ORDERS) {
        Order order;

        if (!(file >> order.orderID)) {
            break;
        }

        if (!(file >> order.customerID >> order.itemCount >> order.total)) {
            cout << "Warning: An order record could not be read.\n";
            break;
        }
        file.ignore(10000, '\n');

        if (order.itemCount < 1 || order.itemCount > MAX_ITEMS_PER_ORDER) {
            cout << "Warning: An order has an invalid number of items.\n";
            break;
        }

        bool validOrder = true;

        for (int i = 0; i < order.itemCount; i++) {
            if (!(file >> order.items[i].menuItemID)) {
                validOrder = false;
                break;
            }
            file.ignore(10000, '\n');

            if (!file.getline(order.items[i].itemName, 50)) {
                validOrder = false;
                break;
            }

            if (!(file >> order.items[i].quantity >> order.items[i].price)) {
                validOrder = false;
                break;
            }
            file.ignore(10000, '\n');

            if (order.items[i].quantity <= 0 || order.items[i].price < 0) {
                validOrder = false;
                break;
            }
        }

        if (!validOrder || order.orderID <= 0 || order.total < 0) {
            cout << "Warning: A damaged order record was skipped.\n";
            break;
        }

        orders[orderCount] = order;
        orderCount++;
    }

    file.close();
}

bool saveOrders() {
    ofstream file("data/orders.txt");

    if (!file) {
        return false;
    }

    for (int i = 0; i < orderCount; i++) {
        file << orders[i].orderID << '\n';
        file << orders[i].customerID << '\n';
        file << orders[i].itemCount << '\n';
        file << orders[i].total << '\n';

        for (int j = 0; j < orders[i].itemCount; j++) {
            file << orders[i].items[j].menuItemID << '\n';
            file << orders[i].items[j].itemName << '\n';
            file << orders[i].items[j].quantity << '\n';
            file << orders[i].items[j].price << '\n';
        }
    }

    file.close();
    return !file.fail();
}

int getOrderCount() {
    return orderCount;
}

float getTotalSales() {
    float totalSales = 0;

    for (int i = 0; i < orderCount; i++) {
        totalSales += orders[i].total;
    }

    return totalSales;
}

void createOrder() {
    cout << "\n========== CREATE ORDER ==========\n";

    if (orderCount >= MAX_ORDERS) {
        cout << "Order storage is full.\n";
        return;
    }

    if (getMenuCount() == 0) {
        cout << "The menu is empty. Add food items before creating an order.\n";
        return;
    }

    Order newOrder;
    newOrder.itemCount = 0;
    newOrder.total = 0;

    // Generate the next order ID using the highest saved order ID.
    newOrder.orderID = 1;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderID >= newOrder.orderID) {
            newOrder.orderID = orders[i].orderID + 1;
        }
    }

    char customerName[50];
    readText("Enter Customer Name: ", customerName, 50);

    newOrder.customerID = findOrAddCustomer(customerName);

    if (newOrder.customerID == -1) {
        cout << "Order could not be created because the customer could not be registered.\n";
        return;
    }

    viewMenu();

    while (true) {
        int itemID = readInt("\nEnter Food Item ID (0 to finish): ");

        if (itemID == 0) {
            break;
        }

        if (itemID < 0) {
            cout << "Item ID must be positive, or enter 0 to finish.\n";
            continue;
        }

        if (newOrder.itemCount >= MAX_ITEMS_PER_ORDER) {
            cout << "This order already has the maximum number of items.\n";
            break;
        }

        MenuItem selectedItem;

        if (!findMenuItemByID(itemID, selectedItem)) {
            cout << "Food item not found. Please enter an ID from the menu.\n";
            continue;
        }

        cout << "Selected: " << selectedItem.name << '\n';
        cout << "Price: Rs. " << selectedItem.price << '\n';

        int quantity = readInt("Enter Quantity: ");

        if (quantity <= 0) {
            cout << "Quantity must be greater than zero. This item was not added.\n";
            continue;
        }

        int itemIndex = newOrder.itemCount;
        newOrder.items[itemIndex].menuItemID = selectedItem.id;
        strcpy(newOrder.items[itemIndex].itemName, selectedItem.name);
        newOrder.items[itemIndex].quantity = quantity;
        newOrder.items[itemIndex].price = selectedItem.price;

        newOrder.total += selectedItem.price * quantity;
        newOrder.itemCount++;

        cout << "Item added to order.\n";
    }

    if (newOrder.itemCount == 0) {
        cout << "Order cancelled because no items were selected.\n";
        return;
    }

    orders[orderCount] = newOrder;
    orderCount++;

    if (saveOrders()) {
        cout << "Order saved successfully.\n";
    } else {
        cout << "Order created in memory, but the file could not be saved.\n";
    }

    cout << "\n===============================================\n";
    cout << "                 RESTROX BILL                  \n";
    cout << "===============================================\n";
    cout << "Order ID: " << newOrder.orderID << '\n';
    cout << "Customer ID: " << newOrder.customerID << '\n';
    cout << "\n" << left << setw(23) << "ITEM"
         << setw(8) << "QTY"
         << setw(12) << "PRICE"
         << "TOTAL\n";
    cout << "------------------------------------------------\n";

    for (int i = 0; i < newOrder.itemCount; i++) {
        cout << left << setw(23) << newOrder.items[i].itemName
             << setw(8) << newOrder.items[i].quantity
             << setw(12) << newOrder.items[i].price
             << newOrder.items[i].quantity * newOrder.items[i].price
             << '\n';
    }

    cout << "------------------------------------------------\n";
    cout << "GRAND TOTAL: Rs. " << newOrder.total << '\n';
    cout << "===============================================\n";
}

void viewOrders() {
    cout << "\n========== ALL ORDERS ==========\n";

    if (orderCount == 0) {
        cout << "No orders available yet.\n";
        return;
    }

    for (int i = 0; i < orderCount; i++) {
        cout << "\nOrder ID: " << orders[i].orderID << '\n';
        cout << "Customer ID: " << orders[i].customerID << '\n';
        cout << "-----------------------------------------------\n";
        cout << left << setw(23) << "ITEM"
             << setw(8) << "QTY"
             << setw(12) << "PRICE"
             << "TOTAL\n";

        for (int j = 0; j < orders[i].itemCount; j++) {
            cout << left << setw(23) << orders[i].items[j].itemName
                 << setw(8) << orders[i].items[j].quantity
                 << setw(12) << orders[i].items[j].price
                 << orders[i].items[j].quantity * orders[i].items[j].price
                 << '\n';
        }

        cout << "Order Total: Rs. " << orders[i].total << '\n';
    }
}

void orderMenu() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "           ORDER MANAGEMENT         \n";
        cout << "====================================\n";
        cout << "1. Create Order\n";
        cout << "2. View Orders\n";
        cout << "3. Back to Main Menu\n";

        choice = readInt("\nEnter your choice: ");

        if (choice == 1) {
            createOrder();
        } else if (choice == 2) {
            viewOrders();
        } else if (choice == 3) {
            cout << "Returning to Main Menu...\n";
        } else {
            cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    } while (choice != 3);
}
