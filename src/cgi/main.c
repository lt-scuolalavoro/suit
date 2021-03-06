#include "../lib/cgi_utils.h"

int main(int argc, char const *argv[])
{
    char *action = getenv("QUERY_STRING");

    printOpeningTags();
    if (!strcmp(action, "btn=ListCandidates"))
    {
        printf("<h1>Suit Database -All candidates</h1>");
        printCandidates("");
    }
    else
    {
        if (!strcmp(action, "btn=NonRemovedCandidates"))
        {
            printf("<h1>Suit Database - Non-removed candidates</h1>");
            // Call the function that executes the query in the db and prints the result in a table
            printCandidates("WHERE deleted = 0");
        }
        else
        {
            if (!strcmp(action, "btn=RemovedCandidates"))
            {
                printf("<h1>Suit Database - Removed candidates</h1>");
                printCandidates("WHERE deleted = 1");
            }
            else
            {
                if (action[0] == 'l')
                {
                    printf("<h1>Suit Database - Search by last name</h1>");
                    char condition[100] = "WHERE lastName = '";
                    action = deleteCharSequence(action, '=');
                    action = replacePlusWithSpaces(action);
                    strcat(condition, action);
                    strcat(condition, "'");
                    printCandidates(condition);
                }
            }
        }
    }
    printClosingTags();

    closeProgram();
    return 0;
}
