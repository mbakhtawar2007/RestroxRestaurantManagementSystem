// Employee module interface.
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

// Loads saved employee records into memory.
void loadEmployees();
// Saves all employees to file; returns false if the file cannot be opened.
bool saveEmployees();
// Returns the number of employees currently in memory.
int getEmployeeCount();

// Runs the Employee Management submenu.
void employeeMenu();
// Adds one employee after validating the ID and salary.
void addEmployee();
// Prints all employees in a formatted table.
void viewEmployees();

#endif
