/*
    Program that drops a database
*/
#include "headers/utils.h"

int main(int argc, char** argv) {
    char query[40];
    char partialQuery[] = "DROP DATABASE ";
    // Check the arguments
    if (argc == 1) {
        printf("Missing dbName.\n");
        return 1;
    }else {
        if (argc > 2){
            printf("Too many arguments.\n");
            return 1;
        }
    }
    // Connect to mysql server
    setupDb("localhost", "root", NULL, NULL);
    
    // Create the query
    strcpy(query, partialQuery);
    strcat(query, argv[1]);
    // Execute the query
    executeQuery(query, "dropped successfully.", argv[1]);

    return 0;
}