#include <mysql.h>
#include <my_global.h>
#include "utils.h"

int main(int argc, char *argv[]){
    char query[350];

    if(argc < 2) {
        printf("Missing dbName.\n");
        return 1;
    }
    if (argc > 2) {
        printf("Too many arguments.\n");
        return 1;
    }
    setupDb("localhost", "root", NULL, argv[1]);

    printf("Enter the query (end with semicolon):\n");
    scanf("%[^;]", query);

    executeQuery(query, ": Operation completed successfully.", argv[1]);

    return 0;
}