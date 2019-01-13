/*
    File that contains useful functions to manage the db
*/

#include <mysql.h>
#include <my_global.h>
#include <signal.h>
#include "cli_utils.h"

void closeProgram(); 
void executeQuery(char*, char*, char*);
void finishWithError();
void setupDb(char*, char*, char*, char*);

MYSQL *con;

// Exit the program closing mysql connection
void closeProgram() {
    mysql_close(con);
    printf("\nBye.\n");
    exit(1);
}
/* Execute query and print a feedback message
    Input: query, text desired to be displayed and a general argument
    Example:
        executeQuery("CREATE TABLE test", "created." "test");
    Prints: test created.
*/
void executeQuery(char* query, char* outputText, char* arg){
    if(mysql_query(con, query)) {
        finishWithError();
    } else {
        printf("%s %s\n",arg,  outputText);
    }
}
// Print mysql error and exit the program
void finishWithError() {
    fprintf(stderr, "\033[1;31merror:\033[0m %s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}
/*  
    Connect to mysql server and check if everything went good. 
    Can terminate the program in case something went wrong.
    Input: server ip, username, password, database name
*/
void setupDb(char* host, char* user, char* passwd, char* db) {
    con = mysql_init(NULL);

    if(con == NULL) {
        finishWithError(con);
    }else {
        printf("MySQL structure creation: ");
        printSuccess();
    }

    if(mysql_real_connect(con, host, user, passwd, db, 0, 0, 0) == NULL){
        finishWithError(con);
    }else {
        printf("Connect to db %s:", db);
        printSuccess();
    }
}