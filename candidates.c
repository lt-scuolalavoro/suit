#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "ctype.h"

struct candidate {
    // Declaration of the structure variables
    bool removed;
    int id;
    // Name and surname must be a maximum of 20 characters
    char firstName[20];
    char lastName[20];
    char birthDate[11]; //array must be of 11 chars to accomodate for the \0 terminator.
    bool employed;
    float salary;
};
// Functions declaration
// This function, given in input a FILE, returns its number of lines;
int evaluateEntriesNumber(FILE * );
// This function, given in input lastName, the struct of the candidates and the numbers of the candidates, returns the age of the person;
char * age(char[], struct candidate * cand, int nCandidates);
void convertDbToCsv(char * , int, struct candidate[]);
int addNewCandidate(FILE * , struct candidate * , int);
void printCandidate(struct candidate * , int);
void removeCandidate(struct candidate * , int);
void refreshDocument(FILE * , struct candidate * , int, char * );
void main() {
    // Database file must be in the same directory level;
    FILE * fp;
    char filename[30] = "database.txt";
    fp = fopen(filename, "r+");
    int nCandidates = evaluateEntriesNumber(fp);
    int choice;
    int i, nCandVisualized;
    char lastName[20];
    char tmpLastName[20];
    int found;
    bool exit=1;
    char choice2;
    // Create dynamic array
    struct candidate * cand = malloc(nCandidates * sizeof(struct candidate));
    // Set the file position to the beginning of fp;
    rewind(fp);
    for (i = 0; i < nCandidates; i++) {
        // Read CSV text file;
        fscanf(fp, "%d,%d,%[^,],%[^,],%[^,],%d,%f", & cand[i].removed, & cand[i].id, cand[i].firstName, cand[i].lastName, cand[i].birthDate, & cand[i].employed, & cand[i].salary);
    }
    // Menu
    do {
        printf("1. Print candidates;\n2. Print deleted candidates;\n3. Search candidate by last name;\n4. Add candidate;\n5. Remove candidate;\n6. Exit.\n");
        do {
            printf("Insert: ");
            scanf("%d", & choice);
            if (choice < 1 || choice > 6) {
                printf("Invalid value.\n");
            }
        } while (choice < 1 || choice > 6);
        printf("\n");
        switch (choice) {
        case 1:
            nCandVisualized = 0;
            for (i = 0; i < nCandidates; i++) {
                if (cand[i].removed == 0) {
                    printCandidate(cand, i);
                    nCandVisualized++;
                }
            }
            if (nCandVisualized == 0) {
                printf("No candidates found.\n");
            }
            break;
        case 2:
            nCandVisualized = 0;
            for (i = 0; i < nCandidates; i++) {
                if (cand[i].removed == 1) {
                    printCandidate(cand, i);
                    nCandVisualized++;
                }
            }
            if (nCandVisualized == 0) {
                printf("No deleted candidates found.\n");
            }
            break;
        case 3:
            printf("Last name: ");
            scanf(" %20[^\n]", lastName);
            found = 0;
            for (i=0; i<sizeof(lastName)/sizeof(char); i++) {
                lastName[i]=tolower(lastName[i]);
            }
            for (i = 0; i < nCandidates; i++) {
                strcpy(tmpLastName, cand[i].lastName);
                for (int j=0; j<sizeof(tmpLastName)/sizeof(char); j++) {
                    tmpLastName[j]=tolower(cand[i].lastName[j]);
                }
                if (strcmp(lastName, tmpLastName) == 0) {
                    if (cand[i].removed == 0) {
                        found = 1;
                        printCandidate(cand, i);
                    }
                }
            }
            if (found == 0) {
                printf("No candidate found with last name: %s", lastName);
            }
            break;
        case 4:
            cand = realloc(cand, (nCandidates + 1) * sizeof(struct candidate));
            nCandidates = addNewCandidate(fp, cand, nCandidates);
            break;
        case 5:
            found = 0;
            printf("Last name: ");
            scanf(" %20[^\n]", lastName);
            for (i = 0; i < nCandidates; i++) {
                if (strcmp(lastName, cand[i].lastName) == 0 && cand[i].removed == 0) {
                    found = 1;
                    removeCandidate(cand, i);
                    printf("%s %s removed.", cand[i].firstName, cand[i].lastName);
                    refreshDocument(fp, cand, nCandidates, filename);
                }
            }
            if (found == 0) {
                printf("No candidate found with last name: %s", lastName);
            }
            break;
        case 6:
            exit=0;
        }
        printf("\n\n");
    } while (exit==1);
    free(cand);
    fclose(fp);
}

char * age(char temp[], struct candidate * cand, int nCandidates) {
    int found = 0;
    for (int i = 0; i < nCandidates; i++) {
        // The function strcmp compares the string pointed to, by str1 to the string pointed to by str2;
        if (strcmp(temp, cand[i].lastName) == 0) {
            found = 1;
            return cand[i].birthDate;
        }
    }
}
void refreshDocument(FILE * fp, struct candidate * cand, int nCand, char * filename) {
    fp = fopen(filename, "r+");
    for (int i = 0; i < nCand; i++) {
        if (cand[i].employed == 0) {
            fprintf(fp, "%d,%d,%s,%s,%s,%d\n", cand[i].removed, cand[i].id, cand[i].firstName, cand[i].lastName, cand[i].birthDate, cand[i].employed);
        } else {
            fprintf(fp, "%d,%d,%s,%s,%s,%d,%.2f\n", cand[i].removed, cand[i].id, cand[i].firstName, cand[i].lastName, cand[i].birthDate, cand[i].employed, cand[i].salary);
        }
    }
    fseek(fp, 0, SEEK_END);
}
void printCandidate(struct candidate * cand, int i) {
    if (cand[i].employed == 1) {
        printf("%s %s %s Salary: %.2f", cand[i].firstName, cand[i].lastName, cand[i].birthDate, cand[i].salary);
    } else {
        printf("%s %s %s (Not employed)", cand[i].firstName, cand[i].lastName, cand[i].birthDate);
    }
    printf("\n");
}
void removeCandidate(struct candidate * cand, int i) {
    cand[i].removed = 1;
}
int evaluateEntriesNumber(FILE * fp) {
    char ch[100];
    int lines = 0;
    int num = 0;
    rewind(fp);
    // While the lines is not NULL increase the counter variable;
    while (fgets(ch, sizeof(ch), fp) != NULL) {
        lines++;
    }
    return lines;
}
// Print the struct array on the text file, each field separated by commas
void convertDbToCsv(char * filename, int nCand, struct candidate cand[]) {
    FILE * fp;
    fp = fopen(filename, "w");
    for (int i = 0; i < nCand; ++i) {
        fprintf(fp, "%d,%s,%s,%s,%d\n", cand[i].id, cand[i].firstName, cand[i].lastName, cand[i].birthDate, cand[i].employed);
    }
    fclose(fp);
}
// Add a new candidate to the struct array and return the updated number of entries
int addNewCandidate(FILE * fp, struct candidate * cand, int nCand) {
    nCand++;
    int i = nCand - 1; //Last position of the array
    cand[i].removed = 0;
    cand[i].id = nCand;
    printf("First name: ");
    scanf(" %20[^\n]", cand[i].firstName);
    printf("Last name: ");
    scanf(" %20[^\n]", cand[i].lastName);
    printf("Birth date: ");
    scanf("%s", cand[i].birthDate);
    char choice;
    do {
        printf("Is the candidate employed? [y/n] ");
        scanf(" %c", & choice);
        if (choice == 'y') {
            cand[i].employed = 1;
            printf("Salary: ");
            scanf("%f", & cand[i].salary);
            fprintf(fp, "\n%d,%d,%s,%s,%s,%d,%.2f", cand[i].removed, cand[i].id, cand[i].firstName, cand[i].lastName, cand[i].birthDate, cand[i].employed, cand[i].salary);
        } else if (choice == 'n') {
            cand[i].employed = 0;
            cand[i].salary = 0.0;
            fprintf(fp, "\n%d,%d,%s,%s,%s,%d", cand[i].removed, cand[i].id, cand[i].firstName, cand[i].lastName, cand[i].birthDate, cand[i].employed);
        } else {
            printf("Invalid value\n");
        }
    } while (choice != 'y' && choice != 'n');
    fseek(fp, 0, SEEK_END);
    return nCand;
}
