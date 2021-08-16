#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <progutil.h>

#define HELP_MSG "Usage: convert-string <text>\nConverts a string to a series of numbers.\n"
#define CHAR_STR "abcdefghijklmnopqrstuvwxyz "

typedef char byte; 
//Performs a binary search on CHAR_STR.
long long binarySearch(char search) {
    size_t low = 0;
    size_t mid;
    size_t high = strlen(CHAR_STR) - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (CHAR_STR[mid] == search) {
            return mid;
        } else if(CHAR_STR[mid] < search) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    printf("Couldn't find element %c\n", search);
    return -1;
}

//Converts a single character from a char to a number.
byte convertChar(char c) {
    long long pos = binarySearch(c);
    if (pos == -1) {
        printf("Error: Couldn't recognise character %c\n", c);
        return 126;
    }
    return (byte) pos;
}

//Converts an array of chars to an array of numbers.
//Returns NULL if an unrecognised char is given.
byte* convertStr(char* str) {
    size_t strsize = strlen(str);
    byte* result = malloc(sizeof(char) * strsize);
    //Loop over every char in str, and add it's number to result.
    for (size_t i = 0; i < strsize; i++) {
        result[i] = convertChar(str[i]);
        //Check for errors
        if (result[i] == 126) {
            printf("Got %i\n", result[i]);
            return NULL;
        }
    }
    return result;
}

int main(int argc, char** argv) {
    if(!checkInputs(argc, argv, 2, HELP_MSG))
        return 1;
    byte* result = convertStr(argv[1]);
    //Return 1 if an error is encountered.
    if (result == NULL) {
        printf("Got null.\n");
        return 1;
    }
    size_t strsize = strlen(argv[1]);
    for (size_t i = 0; i < strsize; i++) {
        printf("%c, ", result[i] + '0' + 1);
    }
    printf("\n");
}