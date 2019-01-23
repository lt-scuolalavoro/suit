#include "string.h"
#include "stdio.h"

void swapStr(char str1[], char str2[]){
    char temp[5];

    strcpy(temp, str1);
    strcpy(str1, str2);
    strcpy(str2, temp);
}