# RESTROX - Restaurant Management System

RESTROX is a beginner-friendly C++ Programming Fundamentals project. It uses structures, fixed-size arrays, functions, loops, conditions, and text files.

## Modules

1. Dashboard
2. Employee Management
3. Customer Management
4. Menu Management
5. Inventory Management
6. Order Management

## Project files

- `main.cpp`: starts the program and displays the main menu.
- `structures.h`: contains the structures used to store records.
- `input.h` and `input.cpp`: contain small input functions that check user input.
- `employee.cpp`: employee records and employee file handling.
- `customer.cpp`: customer records and customer file handling.
- `menu.cpp`: food menu records and menu file handling.
- `inventory.cpp`: ingredient records and inventory file handling.
- `orders.cpp`: order creation, bills, order history, and order file handling.
- `data/`: stores the text files created by RESTROX.

## How to compile on Windows

Open the VS Code terminal in the `RESTROX` project folder and run:

```powershell
g++ -std=c++11 main.cpp input.cpp employee.cpp customer.cpp menu.cpp inventory.cpp orders.cpp -o restrox.exe
```

Run the program with:

```powershell
.\restrox.exe
```

**Important:** Run the program from the `RESTROX` project folder. The program uses the relative folder path `data/` to save and load records.

## File storage

RESTROX loads saved records when it starts. When a new employee, customer, menu item, ingredient, or order is added, the matching text file is updated.

The files are created inside `data/`:

- `employees.txt`
- `customers.txt`
- `menu.txt`
- `inventory.txt`
- `orders.txt`

The first time you run the project, these files do not need to exist. They are created when you add the first record of that type. Keep the `data` folder in the project directory.

The files use a simple format: each field is stored on its own line. This keeps the storage easy to inspect, but avoid editing the files while RESTROX is running.

## Input checks

The program checks for invalid number input, empty text fields, text that is too long, duplicate IDs, invalid IDs, negative salary or price, negative inventory quantity, invalid food item IDs, and non-positive order quantities. It also checks the fixed array limits before adding records.

## Current project limits

- Up to 100 employees, customers, menu items, ingredients, and orders can be stored in memory.
- An order can contain up to 20 item entries.
- Customer IDs are generated automatically, starting from 1001.
- Employee, menu item, and ingredient IDs are entered by the user and must be unique in their own module.
- Inventory quantities are saved, but they are not automatically reduced when an order is placed. That would require linking each menu item to its ingredients through recipes, which is outside this version.
- Data is stored locally in plain text files. This is suitable for this learning project, not for a real restaurant with multiple users.
