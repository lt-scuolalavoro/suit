/*
    Program that executes a query in a database
*/

#include "../lib/mysql_utils.h"

int main(int argc, char *argv[])
{
    char query[350];

    signal(SIGINT, closeProgram); // Ctrl + C event handling
    // Check arguments
    if (argc < 2)
    {
        printf("Missing dbName.\n");
        return 1;
    }
    if (argc > 2)
    {
        printf("Too many arguments.\n");
        return 1;
    }
    // Connect to mysql server
    setupDb("localhost", "root", NULL, argv[1]);

    printf("Enter the query (end with semicolon):\n");
    scanf("%[^;]", query);
    // Execute the query
    executeQuery(query, ": Operation completed successfully.", argv[1]);

    closeProgram();

    return 0;
}