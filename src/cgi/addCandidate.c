#include "../lib/cgi_utils.h"
#include "../lib/cJSON.h"
#include "../lib/cJSON.c"

int main()
{
    char str[1000];
    const cJSON *tmp = NULL;

    char firstName[30];
    char lastName[30];
    char birthDate[12];
    char employed[3];
    char salary[20];
    char query[300];

    printf("Content-type: text/plain\n\n");

    scanf("%s", str);
    cJSON *person = cJSON_Parse(str);

    if (person == NULL)
    {
        printf("Error");
    }

    tmp = cJSON_GetObjectItemCaseSensitive(person, "firstName");
    snprintf(firstName, 29, "%s", tmp->valuestring);

    tmp = cJSON_GetObjectItemCaseSensitive(person, "lastName");
    snprintf(lastName, 29, "%s", tmp->valuestring);

    tmp = cJSON_GetObjectItemCaseSensitive(person, "birthDate");
    snprintf(birthDate, 11, "%s", tmp->valuestring);

    tmp = cJSON_GetObjectItemCaseSensitive(person, "employed");
    snprintf(employed, 2, "%s", tmp->valuestring);

    tmp = cJSON_GetObjectItemCaseSensitive(person, "salary");
    snprintf(salary, 18, "%s", tmp->valuestring);

    setupDbNoOutput("localhost", "root", NULL, "suit");

    sprintf(query, "INSERT INTO Candidate (firstName, lastName, birthDate, employed, salary) VALUES ('%s', '%s', '%s', %s, %s)",
                firstName,
                lastName,
                birthDate,
                employed,
                strcmp(salary, "") == 0 ? "NULL" : salary);

    executeQueryNoOutput(query);

    closeProgram();
    cJSON_Delete(person);

    return 0;
}