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
    // k: comments counter
    int k=0;
    // v: counter
    int v;
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
                // Only if candidates are not over
                if (i<nCandidates-2) {
                    k++;
                } 
           }
        }


    // Menu
    do {
        printf("1. Print candidates;\n2. Print deleted candidates;\n3. Search candidate;\n4. Add candidate;\n5. Remove candidate;\n6. Reformat database\n7. Exit\n");
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
            v = 0;
            do{
                if(v>0)
                    printf("Invalid last name!\n");
                printf("Last name: ");
                scanf(" %20[^\n]", lastName);
                v =+ 1;
            }while(strlen(lastName)<2||strlen(lastName)>19);
            int *index = searchByLastName(candidates, lastName, nCandidates);
            if (*index == -1) {
                printf("No candidate found with last name: %s", lastName);
            } else {
                if(index[1]==-100){
                    printCandidate(candidates, *(index));
                }else{
                    int n=0;
                    while(index[n]!=-100){
                        n +=1;
                    }
                    i=0;
                    printf("There are %d results. Choose the name: ", n);
                    char name[20];
                    v=0;
                    do{
                        if(v>0)
                            printf("Invalid name!\n");
                        printf("First name: ");
                        scanf(" %20[^\n]", name);
                        v =+ 1;
                    }while(strlen(name)<2||strlen(name)>19);
                    int * indexN = searchByName(candidates, index, name, n);
                    if(*indexN == -1){
                        printf("No candidate found with name: %s", name);
                    }else{
                        if(*(indexN+1)==-100){
                            printCandidate(candidates, *(indexN));
                        }else{
                            i = 0;
                            printf("More than one candidates found: ");
                            while(i<n){
                                printCandidate(candidates, *(indexN+i));
                                i++;
                            }
                        }
                    }
                    free(indexN);
                }
            }
            free(index);
            break;
        // Add candidate
        case 4:
            candidates = realloc(candidates, (nCandidates + 1) * sizeof(struct candidate));
            nCandidates = addNewCandidate(filename, candidates, nCandidates);
            break;
        // Remove candidate
        case 5:
            v = 0;
            do{
                if(v>0)
                    printf("Invalid last name!\n");
                printf("Last name: ");
                scanf(" %20[^\n]", lastName);
                v =+ 1;
            }while(strlen(lastName)<2||strlen(lastName)>19);
            int *indexSur = searchByLastName(candidates, lastName, nCandidates);
            if (*indexSur == -1) {
                printf("No candidate found with last name: %s", lastName);
            } else {
                if(indexSur[1]==-100){
                    removeCandidate(candidates, *indexSur);
                    printf("%s %s removed.", candidates[*indexSur].firstName, candidates[*indexSur].lastName);
                    int i;
                    // Temporary variable
                    char j[50];
                    // Set pointer to the beginning of file
                    fseek(fp, 0, SEEK_SET);
                    // Reach correct line
                    for (i=0; i<(*indexSur)+1+k; i++) {
                        // Set pointer to the end of the line
                        fscanf(fp, "%[^\n]", j);
                        // Set pointer to the next line
                        fseek(fp, 2, SEEK_CUR);
                    }
                    // Set pointer to the last char of the previous line
                    fseek(fp, -3, SEEK_CUR);
                    // Print "1" in file
                    fprintf(fp, "1");
                }else{
                    int n=0;
                    while(indexSur[n]!=-100){
                    n +=1;
                    }
                    i=0;
                    printf("There are %d results. Choose the name: ", n);
                    char name[20];
                    v=0;
                    do{
                        if(v>0)
                            printf("Invalid name!\n");
                        printf("Name: ");
                        scanf(" %20[^\n]", name);
                        v =+ 1;
                    }while(strlen(name)<2||strlen(name)>19);
                    int * indexN = searchByName(candidates, indexSur, name, n);
                    if(*indexN == -1){
                        printf("No candidate found with name: %s", name);
                    }else{
                        if(*(indexN+1)==-100){
                            removeCandidate(candidates, *indexN);
                            printf("%s %s removed.", candidates[*indexN].firstName, candidates[*indexN].lastName);
                            int i;
                            // Temporary variable
                            char j[50];
                            // Set pointer to the beginning of file
                            fseek(fp, 0, SEEK_SET);
                            // Reach correct line
                            for (i=0; i<(*indexN)+1+k; i++) {
                                // Set pointer to the end of the line
                                fscanf(fp, "%[^\n]", j);
                                // Set pointer to the next line
                                fseek(fp, 2, SEEK_CUR);
                            }
                            // Set pointer to the last char of the previous line
                            fseek(fp, -3, SEEK_CUR);
                            // Print "1" in file
                            fprintf(fp, "1");
                        }else{
                            i = 0;
                            printf("More than one candidates found: ");
                        }
                    }
                    free(indexN);
                } 
            }
            free(indexSur);
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