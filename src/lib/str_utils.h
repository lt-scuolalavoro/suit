#include "string.h"
#include "stdio.h"

char* deleteCharSequence(char *, char);
char* replacePlusWithSpaces(char *);
void swapStr(char[], char[]);

/* Deletes a sequence of char of a string until the first char 'c'(parameter) is encountered, 
*resizing the string
*/  
char * deleteCharSequence(char* str, char c) {
    while(str[0]!=c){
        memmove(&str[0], &str[1], strlen(str));
    }
    memmove(&str[0], &str[1], strlen(str));
    return str;
}

// Substitutes all '+' with spaces
char * replacePlusWithSpaces(char* str) {
    int i;
    for (i=0; i<strlen(str); i++) {
        if (str[i]=='+') {
            str[i]=' ';
        }
    }
    return str;
}

void swapStr(char str1[], char str2[]){
    char temp[5];

    strcpy(temp, str1);
    strcpy(str1, str2);
    strcpy(str2, temp);
}