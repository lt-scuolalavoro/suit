#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "ctype.h"
#include "utils.h"
#define BUFSIZE 100

void main() {
    // Database file must be in the same directory level;
    FILE * fp;
    char filename[30] = "../database.txt";
    fp = fopen(filename, "r+");
    int nCandidates = evaluateEntriesNumber(fp);
    // Input is now a char[]
    char choice[10];
    int i; // Loops index
    int nCandVisualized;
    // Temporary variable used in the switch
    char lastName[20];
    int index;
    // Input converted in int
    int inputConverted;
    bool exit = 1;
    // Create dynamic array
    struct candidate *candidates = malloc(nCandidates * sizeof(struct candidate));
    // Set the file position to the beginning of fp;
    rewind(fp);
  char txt[BUFSIZE];
    i=0;
    int k=0;
    fseek(fp, 0, SEEK_SET);
    while (!feof(fp)) {
        fscanf(fp, "%c", txt);
        if (txt[0]!='#'){
            fseek(fp, -1, SEEK_CUR);
            candidates[i].salary = 0;
            fscanf(fp, "%d,%[^,],%[^,],%[^,],%d,%f,%d",
            &candidates[i].id,
            candidates[i].firstName,
            candidates[i].lastName,
            candidates[i].birthDate,
            &candidates[i].employed,
            &candidates[i].salary,
            &candidates[i].removed
            );
            fgets(txt, BUFSIZE, fp);
            i++;
           } else {
                fgets(txt,BUFSIZE,fp);
                nCandidates--;
           }
           k++;
        }


    // Menu
    do {
        printf("1. Print candidates;\n2. Print deleted candidates;\n3. Search candidate by last name;\n4. Add candidate;\n5. Remove candidate;\n6. Reformat database\n7. Exit\n");
        do {
            printf("Insert: ");
            scanf("%s", &choice);
            // atoi=cast from char[] to int
            inputConverted=atoi(choice);
            if ((inputConverted < 1 || inputConverted > 7) || isInteger(choice)==0) {
                printf("Invalid value.\n");
            }
        } while ((inputConverted < 1 || inputConverted > 7) || isInteger(choice)==0);
        printf("\n");
        switch (inputConverted) {
        // Print candidates
        case 1:
            printInOrder(candidates, 0, nCandidates);
            break;
        // Print removed candidates
        case 2:
            printInOrder(candidates, 1, nCandidates);
            break;
        // Search for candidate
        case 3:
            printf("Last name: ");
            scanf(" %20[^\n]", lastName);
            index = searchByLastName(candidates, lastName, nCandidates);
            if (index == -1) {
                printf("No candidate found with last name: %s", lastName);
            } else {
                printCandidate(candidates, index);
            }
            break;
        // Add candidate
        case 4:
            printf("%d", nCandidates);
            candidates = realloc(candidates, (nCandidates + 1) * sizeof(struct candidate));
            nCandidates = addNewCandidate(filename, candidates, nCandidates);
            break;
        // Remove candidate
        case 5:
            printf("Last name: ");
            scanf(" %20[^\n]", lastName);
            index = searchByLastName(candidates, lastName, nCandidates);
            if (index == -1) {
                printf("No candidate found with last name: %s", lastName);
            } else {
                removeCandidate(candidates, index);
                printf("%s %s removed.", candidates[index].firstName, candidates[index].lastName);
                int i;
                // Temporary variable
                char j[50];
                // Set pointer to the beginning of file
                fseek(fp, 0, SEEK_SET);
                for (i=0; i<index+1; i++) {
                    // Set pointer to the end of the line
                    fscanf(fp, "%[^\n]", j);
                    // Set pointer to the next line
                    fseek(fp, 2, SEEK_CUR);
                }
                // Set pointer to the last char of the previous line
                fseek(fp, -3, SEEK_CUR);
                // Print "1" in file
                fprintf(fp, "1");
            }
            break;
		// Format structure
        case 6:
          format(filename, nCandidates, candidates);
          break;
        // Exit
        case 7:
            free(candidates);
            fclose(fp);
            exit = 0;
        }
        printf("\n\n");
    } while (exit == 1);
}
