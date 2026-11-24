#ifndef MENU_H
#define MENU_H

#include "structures.h"

void loadMenuItems();
bool saveMenuItems();
int getMenuCount();

void menuManagement();
void addMenuItem();
void viewMenu();
bool findMenuItemByID(int id, MenuItem &item);

#endif
