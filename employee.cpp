// Employee management: load, save, add, and view employee records.
#include <iostream>
#include <fstream>
#include <iomanip>
#include "employee.h"
#include "structures.h"
#include "input.h"

using namespace std;

// Maximum number of employee records stored in memory.
const int MAX_EMPLOYEES = 100;
Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

// Loads employee records from data/employees.txt; skips invalid rows.
void loadEmployees() {
    ifstream file("data/employees.txt");

    // It is normal for this file not to exist on the first run.
    if (!file) {
        return;
    }

    employeeCount = 0;

    while (employeeCount < MAX_EMPLOYEES) {
        Employee employee;

        if (!(file >> employee.id)) {
            break;
        }
        file.ignore(10000, '\n');

        if (!file.getline(employee.name, 50)) break;
        if (!file.getline(employee.role, 30)) break;
        if (!(file >> employee.salary)) break;
        file.ignore(10000, '\n');

        if (employee.id <= 0 || employee.salary < 0) {
            continue;
        }

        employees[employeeCount] = employee;
        employeeCount++;
    }

    file.close();
}

// Rewrites data/employees.txt from memory; returns false if the file cannot be opened.
bool saveEmployees() {
    ofstream file("data/employees.txt");

    if (!file) {
        return false;
    }

    for (int i = 0; i < employeeCount; i++) {
        file << employees[i].id << '\n';
        file << employees[i].name << '\n';
        file << employees[i].role << '\n';
        file << employees[i].salary << '\n';
    }

    file.close();
    return !file.fail();
}

// Returns the number of employees currently in memory.
int getEmployeeCount() {
    return employeeCount;
}

// Adds one employee after checking for a duplicate ID and a negative salary.
void addEmployee() {
    cout << "\n========== ADD EMPLOYEE ==========\n";

    if (employeeCount >= MAX_EMPLOYEES) {
        cout << "Employee storage is full.\n";
        return;
    }

    Employee newEmployee;
    newEmployee.id = readInt("Enter Employee ID: ");

    if (newEmployee.id <= 0) {
        cout << "Employee ID must be greater than zero.\n";
        return;
    }

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == newEmployee.id) {
            cout << "This employee ID already exists.\n";
            return;
        }
    }

    readText("Enter Employee Name: ", newEmployee.name, 50);
    readText("Enter Employee Role: ", newEmployee.role, 30);
    newEmployee.salary = readFloat("Enter Employee Salary: ");

    if (newEmployee.salary < 0) {
        cout << "Salary cannot be negative. Employee was not added.\n";
        return;
    }

    employees[employeeCount] = newEmployee;
    employeeCount++;

    if (saveEmployees()) {
        cout << "Employee added and saved successfully.\n";
    } else {
        cout << "Employee added in memory, but the file could not be saved.\n";
    }
}

// Prints all employees in a formatted table.
void viewEmployees() {
    cout << "\n========== EMPLOYEE RECORDS ==========\n";

    if (employeeCount == 0) {
        cout << "No employees registered yet.\n";
        return;
    }

    cout << left << setw(10) << "ID"
         << setw(25) << "NAME"
         << setw(20) << "ROLE"
         << "SALARY\n";
    cout << "---------------------------------------------------------------\n";

    for (int i = 0; i < employeeCount; i++) {
        cout << left << setw(10) << employees[i].id
             << setw(25) << employees[i].name
             << setw(20) << employees[i].role
             << employees[i].salary << '\n';
    }
}

// Runs the Employee Management submenu until the user goes back.
void employeeMenu() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "         EMPLOYEE MANAGEMENT        \n";
        cout << "====================================\n";
        cout << "1. Add Employee\n";
        cout << "2. View Employees\n";
        cout << "3. Back to Main Menu\n";

        choice = readInt("\nEnter your choice: ");

        if (choice == 1) {
            addEmployee();
        } else if (choice == 2) {
            viewEmployees();
        } else if (choice == 3) {
            cout << "Returning to Main Menu...\n";
        } else {
            cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    } while (choice != 3);
}
