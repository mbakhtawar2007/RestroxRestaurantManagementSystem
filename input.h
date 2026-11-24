#ifndef INPUT_H
#define INPUT_H

// These functions keep user input simple and help prevent invalid values.
int readInt(const char* message);
float readFloat(const char* message);
void readText(const char* message, char text[], int size);

#endif
