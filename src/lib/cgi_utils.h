/*
    Includes functions to manage cgi scripts
*/
#include "mysql_utils.h"
#include "str_utils.h"

void printOpeningTags();
void printClosingTags();
void printCandidates(char *);


// Builds the html page
void printOpeningTags() {
    printf("Content-type: text/html\n\n");
    printf("<!doctype html>\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<link rel='stylesheet' type='text/css' href='../style.css?v=1'>\n");
    printf("</head>\n");
    printf("<body>");
}

// Closes the html page
void printClosingTags() {
    printf("<br>");
    printf("<h2><a href=\"../home.html\">Back</a></h2>\n");
    printf("</body>\n");
    printf("</html>\n");
}

/* Executes SELECT * FROM Candidate in the db and prints the result in a table
    Input: query condition (e.g. WHERE removed = 0)
*/
void printCandidates(char *condition)
{
    // Creates the query
    char query[200] = "";
    strcat(query, "SELECT * FROM Candidate ");
    strcat(query, condition);

    setupDbNoOutput("localhost", "root", NULL, "suit");

    executeQueryNoOutput(query);

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        finishWithError();
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    MYSQL_FIELD *field;

    printf("<table>\n");
    printf("\t<tr>\n");
    while((field = mysql_fetch_field(result))){

        printf("\t\t<th>%s</th>\n", field->name);
    };
    printf("\t</tr>\n");

    while ((row = mysql_fetch_row(result)))
    {
        printf("\t<tr>\n");
        for (int i = 0; i < num_fields; i++)
        {
            printf("\t\t<td>%s</td>\n", row[i] ? row[i] : "NULL");
        }
        printf("\t</tr>\n");
    }
    printf("</table>\n");

    mysql_free_result(result);

}