#include <mysql.h>
#include <my_global.h>

int main(int argc, char** argv) {
    
    char query[40];
    char partialQuery[] = "DROP DATABASE ";
    // Create the pointer
    MYSQL *con = mysql_init(NULL);
    
    if (argc == 1) {
        printf("Which database do you want to drop?\n");
        return 1;
    }else {
        if (argc > 2){
            printf("Too many arguments.\n");
            return 1;
        }
        // Check the pointer
        if(con == NULL) {
            fprintf(stderr, "%s\n", mysql_error(con));
            return 1;
        }else {
            printf("MySQL structure creation: SUCCESS\n");
        }
        // Connect to the localhost server (no password)
        if(mysql_real_connect(con, "localhost", "root", NULL, 0, 0, 0, 0) == NULL){
            fprintf(stderr, "Failed to connect to database. Error: %s\n", mysql_error(con));
            mysql_close(con); // Close the connection
            return 1;
        }else {
            printf("Database connection: SUCCESS\n");
        }
        // Create the query
        strcpy(query, partialQuery);
        strcat(query, argv[1]);
        // Create  database
        if(mysql_query(con, query) != 0) {
            fprintf(stderr, "Failed to drop database. Error: %s\n", mysql_error(con));
            mysql_close(con);
            return 1;
        }else {
            printf("%s database drop: SUCCESS\n", argv[1]);
        }
    }

    return 0;
}