#include "../lib/cgi_utils.h"
#include "../lib/cJSON.h"
#include "../lib/cJSON.c"

int main()
{
    char str[10000];
    const cJSON *tmp = NULL;
    const cJSON *tmp_contact = NULL;

    char firstName[30];
    char lastName[30];
    char birthDate[12];
    char employed[3];
    char salary[20];
    char notes[256];

    int num_contacts;
    int candidateId;
    int index;
    char query[400];

    printf("Content-type: text/plain\n\n");

    scanf("%s", str);
    cJSON *person = cJSON_Parse(str);

    if (person == NULL)
    {
        printf("Error");
    }

    tmp = cJSON_GetObjectItemCaseSensitive(person, "firstName");
    for (index=0; index<29; index++) {
        if (tmp->valuestring[index] == '`') {
            tmp->valuestring[index] = ' ';
        }
    }
    snprintf(firstName, 29, "%s", tmp->valuestring);
    tmp = cJSON_GetObjectItemCaseSensitive(person, "lastName");
    for (index=0; index<29; index++) {
        if (tmp->valuestring[index] == '`') {
            tmp->valuestring[index] = ' ';
        }
    }
    snprintf(lastName, 29, "%s", tmp->valuestring);

    tmp = cJSON_GetObjectItemCaseSensitive(person, "birthDate");
    snprintf(birthDate, 11, "%s", tmp->valuestring);

    tmp = cJSON_GetObjectItemCaseSensitive(person, "employed");
    snprintf(employed, 2, "%s", tmp->valuestring);

    tmp = cJSON_GetObjectItemCaseSensitive(person, "salary");
    snprintf(salary, 18, "%s", tmp->valuestring);

    tmp = cJSON_GetObjectItemCaseSensitive(person, "notes");
    if (tmp != NULL)
    {
        for (index=0; index<255; index++) {
            if (tmp->valuestring[index] == '`') {
               tmp->valuestring[index] = ' ';
            }
        }
        snprintf(notes, 255, "%s", tmp->valuestring);
    }

    setupDbNoOutput("localhost", "root", NULL, "suit");

    sprintf(query, "INSERT INTO Candidate (firstName, lastName, birthDate, employed, salary, notes) VALUES ('%s', '%s', '%s', %s, %s, '%s')",
            firstName,
            lastName,
            birthDate,
            employed,
            strcmp(salary, "") == 0 ? "NULL" : salary,
            strcmp(salary, "") == 0 ? "NULL" : notes);

    executeQueryNoOutput(query);
    // Parse contacts
    tmp = cJSON_GetObjectItemCaseSensitive(person, "contacts");
    num_contacts = cJSON_GetArraySize(tmp);

    char contacts[num_contacts][2][256];
    // Save contacts into this matrix of strings [COL][ROW][STR_LENGTH]
    for (index = 0; index < num_contacts; index++)
    {
        tmp_contact = cJSON_GetArrayItem(tmp, index);
        snprintf(contacts[index][0], 255, "%s", cJSON_GetObjectItemCaseSensitive(tmp_contact, "name")->valuestring);
        snprintf(contacts[index][1], 255, "%s", cJSON_GetObjectItemCaseSensitive(tmp_contact, "link")->valuestring);
    }
    // Take the id of the candidate's contacts
    candidateId = executeIntQuery("SELECT id FROM Candidate ORDER BY ID DESC LIMIT 1");
    // Save contacts to the db
    for (index = 0; index < num_contacts; index++)
    {
        sprintf(query, "INSERT INTO Contacts VALUES (NULL, %d, '%s', '%s')",
                candidateId,
                contacts[index][0],
                contacts[index][1]);

        executeQueryNoOutput(query);
    }

    closeProgram();
    cJSON_Delete(person);

    return 0;
}