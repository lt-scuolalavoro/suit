#include "../lib/cgi_utils.h"
#include "../lib/cJSON.h"
#include "../lib/cJSON.c"

int main()
{
    char str[10000];
    cJSON *tmp = NULL;
    cJSON *tmp_contact = NULL;

    int id;
    char firstName[30];
    char lastName[30];
    char birthDate[12];
    char employed[3];
    int salary;
    char notes[256];

    int num_contacts;
    int removed_contacts_len;
    int index;

    char query[400];

    printf("Content-type: text/plain\n\n");

    scanf("%s", str);
    // strcpy(str, "{\"id\":\"19\",\"firstName\":\"Gianni\",\"lastName\":\"Celeste\",\"birthDate\":\"2019-03-14\",\"employed\":\"1\",\"salary\":\"1300\",\"contacts\":[]}");
    cJSON *person = cJSON_Parse(str);

    if (person == NULL)
    {
        printf("Error");
    }

    tmp = cJSON_GetObjectItemCaseSensitive(person, "id");
    id = atoi(tmp->valuestring);

    tmp = cJSON_GetObjectItemCaseSensitive(person, "firstName");
    for (index=0; index<32; index++) {
        if (tmp->valuestring[index] == '`') {
            tmp->valuestring[index] = ' ';
        }
    }
    snprintf(firstName, 29, "%s", tmp->valuestring);

    tmp = cJSON_GetObjectItemCaseSensitive(person, "lastName");
    for (index=0; index<32; index++) {
        if (tmp->valuestring[index] == '`') {
            tmp->valuestring[index] = ' ';
        }
    }
    snprintf(lastName, 29, "%s", tmp->valuestring);

    tmp = cJSON_GetObjectItemCaseSensitive(person, "birthDate");
    for (index=0; index<32; index++) {
        if (tmp->valuestring[index] == '`') {
            tmp->valuestring[index] = ' ';
        }
    }
    snprintf(birthDate, 11, "%s", tmp->valuestring);

    tmp = cJSON_GetObjectItemCaseSensitive(person, "employed");
    for (index=0; index<32; index++) {
        if (tmp->valuestring[index] == '`') {
            tmp->valuestring[index] = ' ';
        }
    }
    snprintf(employed, 2, "%s", tmp->valuestring);

    tmp = cJSON_GetObjectItemCaseSensitive(person, "salary");
    salary = atoi(tmp->valuestring);

    tmp = cJSON_GetObjectItemCaseSensitive(person, "notes");
    if (tmp != NULL)
    {
        for (index=0; index<255; index++) {
            if (tmp->valuestring[index] == '`') {
                tmp->valuestring[index] = ' ';
            }
        }
        snprintf(notes, index, "%s", tmp->valuestring);
    }

    setupDbNoOutput("localhost", "root", NULL, "suit");

    sprintf(query, "UPDATE Candidate SET firstName = '%s', lastName = '%s', birthDate = '%s', employed = %s, salary = %d, notes = '%s' WHERE id = %d",
            firstName,
            lastName,
            birthDate,
            employed,
            salary,
            notes,
            id);

    executeQueryNoOutput(query);
    // Remove contacts
    tmp = cJSON_GetObjectItemCaseSensitive(person, "removed_contacts_ids");
    removed_contacts_len = cJSON_GetArraySize(tmp);

    for (index = 0; index < removed_contacts_len; index++)
    {
        tmp_contact = cJSON_GetArrayItem(tmp, index);
        for (index=0; index<32; index++) {
            if (tmp_contact->valuestring[index] == '`') {
                tmp_contact->valuestring[index] = ' ';
            }
        }
        sprintf(query, "DELETE FROM Contacts WHERE id = %d", atoi(tmp_contact->valuestring));
        executeQueryNoOutput(query);
    }

    // Parse contacts
    tmp = cJSON_GetObjectItemCaseSensitive(person, "contacts");
    num_contacts = cJSON_GetArraySize(tmp);

    char contacts[num_contacts][2][256];
    int contacts_id[num_contacts];
    // Save contacts into this matrix of strings [COL][ROW][STR_LENGTH]
    for (index = 0; index < num_contacts; index++)
    {
        tmp_contact = cJSON_GetArrayItem(tmp, index);
        contacts_id[index] = atoi(cJSON_GetObjectItemCaseSensitive(tmp_contact, "id")->valuestring);
        snprintf(contacts[index][0], 255, "%s", cJSON_GetObjectItemCaseSensitive(tmp_contact, "name")->valuestring);
        snprintf(contacts[index][1], 255, "%s", cJSON_GetObjectItemCaseSensitive(tmp_contact, "link")->valuestring);
    }

    for (index = 0; index < num_contacts; index++)
    {
        sprintf(query, "INSERT INTO Contacts (name, link, id, candidateId) VALUES ('%s', '%s', %d, %d) ON DUPLICATE KEY UPDATE name = VALUES(name), link = VALUES(link), id = VALUES(id), candidateId = VALUES(candidateId)",
                contacts[index][0],
                contacts[index][1],
                contacts_id[index],
                id);

        executeQueryNoOutput(query);
    }

    closeProgram();
    cJSON_Delete(person);
    cJSON_Delete(tmp_contact);
    cJSON_Delete(tmp);

    return 0;
}