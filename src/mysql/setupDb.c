/*
    Program that executes a query in a database
*/

#include "../lib/mysql_utils.h"

int main(int argc, char *argv[])
{
    char query[250];
    signal(SIGINT, closeProgram); // Ctrl + C event handling
    // Connect to mysql server
    setupDb("localhost", "root", NULL, NULL);
    strcpy(query, "CREATE DATABASE suit");
    executeQuery(query, ": Operation completed successfully.", "Create DB");
    closeConnection();

    setupDb("localhost", "root", NULL, "suit");
    strcpy(query, "CREATE TABLE Candidate ("
                  "id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                  "firstName VARCHAR(20),"
                  "lastName VARCHAR(20),"
                  "birthDate DATE,"
                  "employed TINYINT,"
                  "salary FLOAT,"
                  "removed TINYINT)");

    executeQuery(query, ": Operation completed successfully.", "Create Table");

    strcpy(query, "INSERT INTO Candidate VALUES (NULL, 'Emanuele', 'Rizzi', '2000-01-01', 0, 0, 0)");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query, "INSERT INTO Candidate VALUES (NULL, 'Giuseppe', 'De Santis', '2000-01-01', 0, 0, 0)");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query, "INSERT INTO Candidate VALUES (NULL, 'Giuseppe', 'Lepore', '2000-01-01', 0, 0, 0)");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query, "INSERT INTO Candidate VALUES (NULL, 'Marcello', 'Tarallo', '2000-01-01', 0, 0, 0)");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query, "INSERT INTO Candidate VALUES (NULL, 'Martino', 'Pagano', '2000-01-01', 0, 0, 0)");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query, "INSERT INTO Candidate VALUES (NULL, 'Raffaele', 'Del Basso', '2000-01-01', 0, 0, 0)");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query, "INSERT INTO Candidate VALUES (NULL, 'Roberto', 'Clemente', '2000-01-01', 0, 0, 0)");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query, "INSERT INTO Candidate VALUES (NULL, 'Simone', 'Cacciapaglia', '2000-01-01', 0, 0, 0)");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query, "INSERT INTO Candidate VALUES (NULL, 'Simone', 'Verna', '2000-01-01', 0, 0, 0)");
    executeQuery(query, ": Operation completed successfully.", "Insert");

    closeProgram();

    return 0;
}