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
    char birthDate[11]; // Array must be of 11 chars to accomodate for the \0 terminator.
    bool employed;
    float salary;
};
// Functions declaration
int evaluateEntriesNumber(FILE * );
char * age(char[], struct candidate * cand, int nCandidates);
void convertDbToCsv(char * , int, struct candidate[]);
int addNewCandidate(char * , struct candidate * , int);
void printCandidate(struct candidate * , int);
void removeCandidate(struct candidate * , int);
void updateDatabase(FILE * , struct candidate * , int, char * );
int searchByLastName(struct candidate * , char * , int);
void main() {
    // Database file must be in the same directory level;
    FILE * fp;
    char filename[30] = "database.txt";
    fp = fopen(filename, "r+");
    int nCandidates = evaluateEntriesNumber(fp);
    int choice;
    int i; // Loops index
    int nCandVisualized;
    // Temporary variable used in the switch
    char lastName[20];
    int index;
    bool exit = 1;
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
            // Print candidates
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
            // Print removed candidates
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
            // Search for candidate
        case 3:
            printf("Last name: ");
            scanf(" %20[^\n]", lastName);
            index = searchByLastName(cand, lastName, nCandidates);
            if (index == -1) {
                printf("No candidate found with last name: %s", lastName);
            } else {
                printCandidate(cand, index);
            }
            break;
            // Add candidate
        case 4:
            cand = realloc(cand, (nCandidates + 1) * sizeof(struct candidate));
            nCandidates = addNewCandidate(filename, cand, nCandidates);
            break;
            // Remove candidate
        case 5:
            printf("Last name: ");
            scanf(" %20[^\n]", lastName);
            index = searchByLastName(cand, lastName, nCandidates);
            if (index == -1) {
                printf("No candidate found with last name: %s", lastName);
            } else {
                removeCandidate(cand, index);
                printf("%s %s removed.", cand[index].firstName, cand[index].lastName);
                updateDatabase(fp, cand, nCandidates, filename);
            }
            break;
            // Exit
        case 6:
            free(cand);
            fclose(fp);
            exit = 0;
        }
        printf("\n\n");
    } while (exit == 1);
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
void updateDatabase(FILE * fp, struct candidate * cand, int nCand, char * filename) {
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
// Search for a candidate into the struct (case insensitive)
// I: Array of struct candidate, candidate Last Name, number of entries
// O: Index of the candidate in array or -1 if not found
int searchByLastName(struct candidate * cand, char * lastName, int nEntries) {
    char tmpLastName[20];
    int i = 0;
    int index = -1;
    // Transform input to lower case
    while (lastName[i] != '0' && i < 20) {
        lastName[i] = tolower(lastName[i]);
        i++;
    }
    i = 0;
    do {
        // Transform lastName to lower case
        if (cand[i].removed == 0) {
            for (int j = 0; j < sizeof(tmpLastName) / sizeof(char); j++) {
                tmpLastName[j] = tolower(cand[i].lastName[j]);
            }
            if (strcmp(lastName, tmpLastName) == 0) {
                index = i;
            }
        }
        i++;
    } while (index == -1 && i < nEntries);
    return index;
}
// Function that prints the chosen candidate
void printCandidate(struct candidate * cand, int i) {
    if (cand[i].employed == 1) {
        printf("%s %s %s Salary: %.2f", cand[i].firstName, cand[i].lastName, cand[i].birthDate, cand[i].salary);
    } else {
        printf("%s %s %s (Not employed)", cand[i].firstName, cand[i].lastName, cand[i].birthDate);
    }
    printf("\n");
}
// Function that sets removed equals to 1 to the chosen candidate
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
int addNewCandidate(char * filename, struct candidate * cand, int nCand) {
    FILE * fp;
    // Reopen the file in append mode
    fp = fopen(filename, "a");
    nCand++;
    int i = nCand - 1; // Last position of the array
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
            fprintf(fp, "%d,%d,%s,%s,%s,%d,%.2f\n", cand[i].removed, cand[i].id, cand[i].firstName, cand[i].lastName, cand[i].birthDate, cand[i].employed, cand[i].salary);
        } else if (choice == 'n') {
            cand[i].employed = 0;
            cand[i].salary = 0.0;
            fprintf(fp, "%d,%d,%s,%s,%s,%d\n", cand[i].removed, cand[i].id, cand[i].firstName, cand[i].lastName, cand[i].birthDate, cand[i].employed);
        } else {
            printf("Invalid value\n");
        }
    } while (choice != 'y' && choice != 'n');
    fclose(fp);
    return nCand;
}
