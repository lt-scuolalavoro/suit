#include "../lib/cgi_utils.h"

int main(int argc, char const *argv[])
{
    char *action = getenv("QUERY_STRING");

    printf("Content-type: text/html\n\n");
    // Build the html page
    printf("<!doctype html>\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<link rel='stylesheet' type='text/css' href='../style.css?v=1'>\n");
    printf("</head>\n");
    printf("<body>\n");
    
    if(!strcmp(action, "btn=2")) {
    	// Call the function that executes the query in the db and prints the result in a table
        printCandidates("WHERE removed = 0");
    } else {
    	if(!strcmp(action, "btn=3")) {
    		printCandidates("WHERE removed = 1");
    	}
    }

    printf("<br>");
    printf("<a href=\"../home.html\">Back</a>\n");
    printf("</body>\n");
    printf("</html>\n");

    closeProgram();
    return 0;
}


