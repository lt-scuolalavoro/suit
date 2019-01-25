/*
    Includes functions to manage cgi scripts
*/
#include "mysql_utils.h"

void printCandidates(char *);

/* Executes SELECT * FROM Candidate in the db and prints the result in a table
    Input: query condition (e.g. WHERE firstName = 'foo')
*/
void printCandidates(char *condition)
{
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