#include "../lib/mysql_utils.h"
#include "../lib/cJSON.h"
#include "../lib/cJSON.c"

int main(){
    MYSQL_FIELD *field;
    MYSQL_ROW row;
    int numFields, index;
    // Json instance creation ( only [])
    cJSON *users = cJSON_CreateArray();
    cJSON *user;
    cJSON *string;
    char **fields;
    int len;
    char *param = getenv("QUERY_STRING");

    char query[300];
    strcat(query, "SELECT * FROM Candidate WHERE ");
    strcat(query, param);

    // Connect to database : ("ip", "user", "psw", "database")
    setupDbNoOutput("localhost", "root", NULL, "suit");
    // Execute the query
    executeQueryNoOutput(query);
    // Save the result of qubery in 'result'
    MYSQL_RES *result = mysql_store_result(con);  
    // Get max fields (Column)
    numFields = mysql_num_fields(result);
    fields = malloc(sizeof(char *) * numFields);

    for(index = 0; index < numFields; index++){
        // Insert in 'field' the next field
        field = mysql_fetch_field(result);
        len = strlen(field->name);
        // Allocate the length of fields
        fields[index] = (char *) malloc(sizeof(char) * len);
        // Copy the contenent of field in fields
        strcpy(fields[index], field->name);
    }

    // While row != NULL, get all contenent of row
    while((row = mysql_fetch_row(result))!=NULL){
        // Object instance creation ( only {})
        user = cJSON_CreateObject();
        for(index = 0; index < numFields; index++){
            // Insert in string the value of single column
             string = cJSON_CreateString(row[index]);
            //  Add to object 'user' the name of column and the value
             cJSON_AddItemToObject(user, fields[index], string);
        }
        // Add to 'users' the row 
        cJSON_AddItemToArray(users, user);
    }
    // Tells the program to print on the file
    printf("Content-type:text/plain\n\n");
    printf("%s", cJSON_Print(users));    
    
    cJSON_Delete(users);    
    free(fields);
    closeProgram();    
    return 0;
}