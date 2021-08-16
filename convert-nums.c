#include <stdio.h>
#include <stdlib.h>
#include <progutil.h>

#define HELP_MSG "Usage: convert-nums <[numbers]>\nConverts a serires of numbers to a string.\n"
#define CHARS "abcdefghijklmnopqrstuvwxyz "

//Converts a number to a char.
char convertNum(int num) {
    return CHARS[num - 1];
}

int main(int argc, char** argv) {
    if(!checkInputs(argc, argv, 2, HELP_MSG))
        return 1;
    //Loop over every number and print out it's respective char.
    for (int i = 1; i < argc; i++) {
        printf("%c", convertNum(atoi(argv[i])));
    }
    printf("\n");
}