#include "coin.h"

// Check if a character is a digit
int isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

// Check if a character is a lowercase letter
int isLowerCase(char ch) {
    return (ch >= 'a' && ch <= 'z');
}

// Check if a character is a special character (defined set)
int isSpecialChar(char ch) {
    return (ch == '!' || ch == '@' || ch == '#' || ch == '$' || ch == '%' || ch == '^');
}

// Check if a character is an uppercase letter
int isUpperCase(char ch) {
    return (ch >= 'A' && ch <= 'Z');
}

// Find the first occurrence of a character in a string
char* stringCharacter(char str[], char ch) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) {
            return &str[i];  // Return the address of the first occurrence of ch
        }
    }
    return NULL;  // Return NULL if ch is not found in the string
}

// Compare two strings for equality
int stringCompare(char destination[MAX_LENGTH], char source[MAX_LENGTH]) {
    int i = 0;
    
    while(destination[i] != '\0' && source[i] != '\0') {
        if(destination[i] != source[i]) {
            return 0;  // Return immediately if characters differ
        }
        i++;
    }

    // After the loop, check if both strings ended
    return (destination[i] == '\0' && source[i] == '\0') ? 1 : 0;
}

// Copy a string from source to destination
void stringCopy(char destination[MAX_LENGTH], char source[MAX_LENGTH]) {
    int i;
    for (i = 0; i < MAX_LENGTH - 1; i++) {  // Reserve space for null terminator
        if (source[i] == '\0') {
            break;
        }
        destination[i] = source[i];
    }
    destination[i] = '\0';  // Ensure the destination is null-terminated
}

// Calculate the length of a string
int stringLength(char array[MAX_LENGTH]) {
    int size = 0;
    while(size < MAX_LENGTH && array[size] != '\0') {
        size++;
    }
    return size;
}
