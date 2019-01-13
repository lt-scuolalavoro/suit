#include <mysql.h>
#include <my_global.h>
#include <signal.h>
#include "utils.h"

int main(int argc, char** argv) {
    char query[300];
    char partialQuery[] = "CREATE TABLE ";
    char column[60];
    int nColumns;
    int i;

    signal(SIGINT, closeProgram); // Ctrl + C event handling
    // Check the arguments
    if (argc == 1) {
        printf("Missing dbName and tableName.\n");
        return 1;
    }
    if (argc == 2) {
        printf("Missing tableName.\n");
           return 1;  
    }
    if (argc > 3){
        printf("Too many arguments.\n");
        return 1;
    }
    setupDb("localhost", "root", NULL, argv[1]);
    // Input phase
    printf("Enter the number of columns of your table: ");
    scanf("%d", &nColumns);
    strcpy(query, partialQuery);
    strcat(query, argv[2]);
    strcat(query, "(");
    
    printf("\nEnter columns information.\n");
    printf("Format: [name] [type]\n");
    for(i = 1; i <= nColumns; i++){
        memset(column, ' ', sizeof(column)/sizeof(char));
        printf("Column %d: ", i);
        scanf(" %60[^\n]", column);
        if(i > 1) {
            strcat(query, ", ");
        }
        strcat(query, column);
    }
    strcat(query, ")");
    // End input phase
    
    // Execute the query
    executeQuery(query, "created successfully.", argv[2]);

    return 0;
}