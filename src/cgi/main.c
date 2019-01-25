#include "../lib/cgi_utils.h"

int main(int argc, char const *argv[])
{
    char *action = getenv("QUERY_STRING");

    printOpeningTags();
    
    if(!strcmp(action, "btn=2")) {
    	printf("<h1>Suit Database - Candidati non rimossi</h1>");
    	// Call the function that executes the query in the db and prints the result in a table
        printCandidates("WHERE removed = 0");
    } else {
    	if(!strcmp(action, "btn=3")) {
    		printf("<h1>Suit Database - Candidati rimossi</h1>");
    		printCandidates("WHERE removed = 1");
    	}
    }
    
    printClosingTags();

    closeProgram();
    return 0;
}
