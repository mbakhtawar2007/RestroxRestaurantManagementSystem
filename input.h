// Validated console input helpers shared by all modules.
#ifndef INPUT_H
#define INPUT_H

// These functions keep user input simple and help prevent invalid values.
// Reads a whole number; reprompts on invalid input such as 5abc.
int readInt(const char* message);
// Reads a decimal number; reprompts on invalid input.
float readFloat(const char* message);
// Reads a non-empty text line within the given size; reprompts when empty or too long.
void readText(const char* message, char text[], int size);

#endif
