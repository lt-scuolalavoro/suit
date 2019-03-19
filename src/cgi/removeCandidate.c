#include "../lib/cgi_utils.h"
#include "../lib/cJSON.h"
#include "../lib/cJSON.c"

int main(){
    char *params = getenv("QUERY_STRING");
    cJSON *tmp = NULL;
    cJSON *json = NULL;

    char id[10001];
    char query[300];

    scanf("%s", params);
    printf("Content-type: text/plain\n\n");
    
    json = cJSON_Parse(params);

    if (json == NULL)
    {
        printf("Error");
    }

    tmp = cJSON_GetObjectItemCaseSensitive(json, "id");
    snprintf(id, 10001, "%s", tmp->valuestring);

    sprintf(query, "UPDATE Candidate SET removed = 1 WHERE id = %s", id);
    printf("%s", query);

    setupDbNoOutput("localhost", "root", NULL, "suit");
    executeQueryNoOutput(query);

    closeProgram();
    cJSON_Delete(json);

    return 0;
}