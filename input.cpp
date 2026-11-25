// Validated console input: every read reprompts until the input is usable.
#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <cstdlib>
#include "input.h"

using namespace std;

// Reads a whole number; reprompts on invalid input such as 5abc.
int readInt(const char* message) {
    int value;
    string line;

    while (true) {
        cout << message;

        if (!getline(cin, line)) {
            cout << "\nInput ended. Closing RESTROX.\n";
            exit(0);
        }

        stringstream input(line);
        char extraCharacter;

        // The second check rejects input such as "5abc".
        if ((input >> value) && !(input >> extraCharacter)) {
            return value;
        }

        cout << "Invalid input. Please enter a whole number.\n";
    }
}

// Reads a decimal number; reprompts on invalid input.
float readFloat(const char* message) {
    float value;
    string line;

    while (true) {
        cout << message;

        if (!getline(cin, line)) {
            cout << "\nInput ended. Closing RESTROX.\n";
            exit(0);
        }

        stringstream input(line);
        char extraCharacter;

        if ((input >> value) && !(input >> extraCharacter)) {
            return value;
        }

        cout << "Invalid input. Please enter a number.\n";
    }
}

// Reads a non-empty text line within the given size; reprompts when empty or too long.
void readText(const char* message, char text[], int size) {
    while (true) {
        cout << message;

        cin.getline(text, size);

        if (cin.fail()) {
            if (cin.eof()) {
                cout << "\nInput ended. Closing RESTROX.\n";
                exit(0);
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input is too long. Please try again.\n";
        } else if (text[0] == '\0') {
            cout << "This field cannot be empty. Please try again.\n";
        } else {
            return;
        }
    }
}
