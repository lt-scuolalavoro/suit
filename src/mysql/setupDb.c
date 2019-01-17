/*
    Program that executes a query in a database
*/

#include "../lib/mysql_utils.h"

int main(int argc, char *argv[]){
    char query[250];
    signal(SIGINT, closeProgram); // Ctrl + C event handling
    // Connect to mysql server
    setupDb("localhost", "root", NULL, NULL);
    strcpy(query, "CREATE DATABASE suit");
    executeQuery(query, ": Operation completed successfully.", "Create DB");
    closeConnection();

    setupDb("localhost", "root", NULL, "suit");
    strcpy(query,"CREATE TABLE Candidate (id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, firstName VARCHAR(20), lastName VARCHAR(20))");
    executeQuery(query, ": Operation completed successfully.", "Create Table");

    strcpy(query,"INSERT INTO Candidate VALUES (NULL, 'Giuseppe', 'Lepore')");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query,"INSERT INTO Candidate VALUES (NULL, 'Martino', 'Pagano')");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query,"INSERT INTO Candidate VALUES (NULL, 'Simone', 'Verna')");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query,"INSERT INTO Candidate VALUES (NULL, 'Roberto', 'Clemente')");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query,"INSERT INTO Candidate VALUES (NULL, 'Simone', 'Cacciapaglia')");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query,"INSERT INTO Candidate VALUES (NULL, 'Emanuele', 'Rizzi')");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query,"INSERT INTO Candidate VALUES (NULL, 'Marcello', 'Tarallo')");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query,"INSERT INTO Candidate VALUES (NULL, 'Raffaele', 'Del Basso')");
    executeQuery(query, ": Operation completed successfully.", "Insert");
    strcpy(query,"INSERT INTO Candidate VALUES (NULL, 'Giuseppe', 'De Santis')");
    executeQuery(query, ": Operation completed successfully.", "Insert");

    closeProgram();

    return 0;
}