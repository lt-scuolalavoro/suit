#include "../lib/mysql_utils.h"
#include "../lib/str_utils.h"
#include "../lib/cJSON.h"
#include "../lib/cJSON.c"

int main()
{
    MYSQL_FIELD *field;
    MYSQL_ROW row;
    MYSQL_ROW contacts_row;
    MYSQL_RES *contacts_result;
    int index;
    // Json instance creation ( only [])
    cJSON *candidates = cJSON_CreateArray();
    cJSON *candidate;
    cJSON *contacts;
    cJSON *contact;
    cJSON *string;

    int numFields, contacts_num_fields;
    char **fields;
    char **contacts_fields;

    char query[255];
    char *param = getenv("QUERY_STRING");

    int len;
    int candidateId;

    // Connect to database : ("ip", "candidate", "psw", "database")
    setupDbNoOutput("localhost", "root", NULL, "suit");
    sprintf(query, "SELECT * FROM Candidate WHERE %s", param);
    deleteCharSequence(param, '=');
    candidateId = atoi(param);
    // Execute the query
    executeQueryNoOutput(query);
    // Save the result of qubery in 'result'
    MYSQL_RES *result = mysql_store_result(con);
    // Get max fields (Column)
    numFields = mysql_num_fields(result);
    fields = malloc(sizeof(char *) * numFields);
    // Fetch Candidate fields
    for (index = 0; index < numFields; index++)
    {
        // Insert in 'field' the next field
        field = mysql_fetch_field(result);
        len = strlen(field->name);
        // Allocate the length of fields
        fields[index] = (char *)malloc(sizeof(char) * len);
        // Copy the contenent of field in fields
        strcpy(fields[index], field->name);
    }
    row = mysql_fetch_row(result);
    // Object instance creation ( only {})
    candidate = cJSON_CreateObject();
    for (index = 0; index < numFields; index++)
    {
        // Insert in string the value of single column
        string = cJSON_CreateString(row[index]);
        //  Add to object 'candidate' the name of column and the value
        cJSON_AddItemToObject(candidate, fields[index], string);
    }
    contacts = cJSON_CreateArray();

    sprintf(query, "SELECT * FROM Contacts WHERE candidateId = %d", candidateId);
    executeQueryNoOutput(query);
    contacts_result = mysql_store_result(con);

    // Get max fields (Column)
    contacts_num_fields = mysql_num_fields(contacts_result);
    contacts_fields = malloc(sizeof(char *) * contacts_num_fields);
    // Save Contacts field names
    for (index = 0; index < contacts_num_fields; index++)
    {
        // Insert in 'field' the next field
        field = mysql_fetch_field(contacts_result);
        len = strlen(field->name);
        // Allocate the length of fields
        contacts_fields[index] = (char *)malloc(sizeof(char) * len);
        // Copy the contenent of field in fields
        strcpy(contacts_fields[index], field->name);
    }
    // Fetch Contacts records
    while ((contacts_row = mysql_fetch_row(contacts_result)) != NULL)
    {
        contact = cJSON_CreateObject();

        for (index = 0; index < contacts_num_fields; index++)
        {
            // Insert in string the value of single column
            string = cJSON_CreateString(contacts_row[index]);
            //  Add to object 'contact' the name of the column and the value
            cJSON_AddItemToObject(contact, contacts_fields[index], string);
        }

        cJSON_AddItemToArray(contacts, contact);
    }

    cJSON_AddItemToObject(candidate, "contacts", contacts);
    // Add the row to 'candidates'
    cJSON_AddItemToArray(candidates, candidate);

    // Tells the program to print on the file
    printf("Content-type:text/plain\n\n");
    printf("%s", cJSON_Print(candidates));

    cJSON_Delete(candidates);
    free(fields);
    closeProgram();
    return 0;
}