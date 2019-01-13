#include <mysql.h>
#include <my_global.h>
#include "utils.h"

int main(int argc, char** argv) {
    
    char query[40];
    char partialQuery[] = "CREATE DATABASE ";
    // Create the pointer
    con = mysql_init(NULL);
    // Check arguments passed
    if (argc == 1) {
        printf("Missing dbName.\n");
        return 1;
    }else {
        if (argc > 2){
            printf("Too many arguments.\n");
            return 1;
        }
    }
    setupDb("localhost", "root", NULL, NULL);

    // Create the query ("CREATE DATABASE + argv[1]")
    strcpy(query, partialQuery);
    strcat(query, argv[1]);
    // Execute query
    executeQuery(query, "created successfully.", argv[1]);

    return 0;
}