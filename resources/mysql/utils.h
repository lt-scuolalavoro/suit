#include <mysql.h>
#include "cli_utils.h"

void closeProgram();
void executeQuery(char*, char*, char*);
void finishWithError();
void setupDb(char*, char*, char*, char*);

MYSQL *con;

void closeProgram() {
    mysql_close(con);
    printf("\nBye.\n");
    exit(1);
}

void executeQuery(char* query, char* outputText, char* arg){
    if(mysql_query(con, query)) {
        finishWithError();
    } else {
        printf("%s %s\n",arg,  outputText);
    }
}

void finishWithError() {
    fprintf(stderr, "\033[1;31merror:\033[0m %s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

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