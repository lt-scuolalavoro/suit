#include "../lib/cgi_utils.h"
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
    cJSON *contacts;
    cJSON *contact;
    cJSON *string;

    int numFields, contacts_num_fields;
    char **fields;
    char **contacts_fields;

    char query[255];

    int len;
    int candidateId = 1;

    setupDbNoOutput("localhost", "root", NULL, "suit");

    // ----Contacts start-----
    contacts = cJSON_CreateArray();

    sprintf(query, "SELECT * FROM Contacts");
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

    // ----Contacts end-----
    printf("Content-type: text/plain\n\n");
    printf("%s", cJSON_Print(contacts));

    closeProgram();
    cJSON_Delete(contacts);
    cJSON_Delete(contact);
    cJSON_Delete(string);

    return 0;
}