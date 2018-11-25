#pragma once
#include "stdio.h"
#include "stdbool.h"

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
void convertDbToCsv(char * , int, struct candidate*);
int addNewCandidate(char * , struct candidate * , int);
void printCandidate(struct candidate * , int);
void removeCandidate(struct candidate * , int);
void updateDatabase(FILE * , struct candidate * , int, char * );
int searchByLastName(struct candidate * , char * , int);
void formatDateInSQL(char*, int, struct candidate*);
void format(char*, int, struct candidate*);

void updateDatabase(FILE * fp, struct candidate * candidates, int nCand, char * filename) {
    fp = fopen(filename, "r+");
    for (int i = 0; i < nCand; i++) {
        if (candidates[i].employed == 0) {
            fprintf(fp, "%d,%d,%s,%s,%s,%d\n", candidates[i].removed, candidates[i].id, candidates[i].firstName, candidates[i].lastName, candidates[i].birthDate, candidates[i].employed);
        } else {
            fprintf(fp, "%d,%d,%s,%s,%s,%d,%.2f\n", candidates[i].removed, candidates[i].id, candidates[i].firstName, candidates[i].lastName, candidates[i].birthDate, candidates[i].employed, candidates[i].salary);
        }
    }
    fseek(fp, 0, SEEK_END);
}
// Search for a candidate into the struct (case insensitive)
// I: Array of struct candidate, candidate Last Name, number of entries
// O: Index of the candidate in array or -1 if not found
int searchByLastName(struct candidate * candidates, char * lastName, int nEntries) {
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
        if (candidates[i].removed == 0) {
            for (int j = 0; j < sizeof(tmpLastName) / sizeof(char); j++) {
                tmpLastName[j] = tolower(candidates[i].lastName[j]);
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
void printCandidate(struct candidate * candidates, int i) {
    if (candidates[i].employed == 1) {
        printf("%s %s %s Salary: %.2f", candidates[i].firstName, candidates[i].lastName, candidates[i].birthDate, candidates[i].salary);
    } else {
        printf("%s %s %s (Not employed)", candidates[i].firstName, candidates[i].lastName, candidates[i].birthDate);
    }
    printf("\n");
}
// Function that sets removed equals to 1 to the chosen candidate
void removeCandidate(struct candidate * candidates, int i) {
    candidates[i].removed = 1;
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
void convertDbToCsv(char * filename, int nCand, struct candidate *candidates) {
    FILE * fp;
    fp = fopen(filename, "w");
    for (int i = 0; i < nCand; ++i) {
        fprintf(fp, "%d,%s,%s,%s,%d\n", candidates[i].id, candidates[i].firstName, candidates[i].lastName, candidates[i].birthDate, candidates[i].employed);
    }
    fclose(fp);
}
// Add a new candidate to the struct array and return the updated number of entries
int addNewCandidate(char * filename, struct candidate * candidates, int nCand) {
    FILE * fp;
    // Reopen the file in append mode
    fp = fopen(filename, "a");
    nCand++;
    int i = nCand - 1; // Last position of the array
    candidates[i].removed = 0;
    candidates[i].id = nCand;
    printf("First name: ");
    scanf(" %20[^\n]", candidates[i].firstName);
    printf("Last name: ");
    scanf(" %20[^\n]", candidates[i].lastName);
    printf("Birth date: ");
    scanf("%s", candidates[i].birthDate);
    char choice;
    do {
        printf("Is the candidate employed? [y/n] ");
        scanf(" %c", & choice);
        if (choice == 'y') {
            candidates[i].employed = 1;
            printf("Salary: ");
            scanf("%f", & candidates[i].salary);
            fprintf(fp, "%d,%d,%s,%s,%s,%d,%.2f\n", candidates[i].removed, candidates[i].id, candidates[i].firstName, candidates[i].lastName, candidates[i].birthDate, candidates[i].employed, candidates[i].salary);
        } else if (choice == 'n') {
            candidates[i].employed = 0;
            candidates[i].salary = 0.0;
            fprintf(fp, "%d,%d,%s,%s,%s,%d\n", candidates[i].removed, candidates[i].id, candidates[i].firstName, candidates[i].lastName, candidates[i].birthDate, candidates[i].employed);
        } else {
            printf("Invalid value\n");
        }
    } while (choice != 'y' && choice != 'n');
    fclose(fp);
    return nCand;
}

void formatDateInSQL(char* filename, int nCand, struct candidate *candidates){
  printf("we lo zi\n");
  FILE * fp;
  fp = fopen(filename, "w");
  char *elements[3], *p, newDate[11];
  int i, j=0;
  for(i = 0; i < nCand; i++){
    p = strtok(candidates[i].birthDate, "/");
    while(p != NULL){
      elements[j] = p;
      p = strtok(NULL, "/");
      j++;
    }
    j = 0;
    strcpy(newDate, "");
    strcat(newDate, elements[2]);
    strcat(newDate, "-");
    strcat(newDate, elements[1]);
    strcat(newDate, "-");
    strcat(newDate, elements[0]);

    strcpy(candidates[i].birthDate, newDate);

    fprintf(fp, "%d,%d,%s,%s,%s,%d,%.2f\n",
        candidates[i].removed,
        candidates[i].id,
        candidates[i].firstName,
        candidates[i].lastName,
        candidates[i].birthDate,
        candidates[i].employed,
        candidates[i].salary
    );

  }
  fclose(fp);
}

void format(char* filename, int nCand, struct candidate *candidates){
  int choice;
  bool exit = 1;

  do {
    printf("What would you like to do?:\n1. Separate values with comma;\n2. change data form in mySQL compatible;\n3. Exit.\n");
    do {
        printf("Insert: ");
        scanf("%d", & choice);
        if (choice < 1 || choice > 3) {
            printf("Invalid value.\n");
          }
    } while (choice < 1 || choice > 3);


      switch (choice){
        case 1:
          convertDbToCsv(filename, nCand, candidates);
        break;

        case 2:
          formatDateInSQL(filename, nCand, candidates);
        break;

        case 3:
          exit = 0;
        break;
      }
  } while(exit == 1);
}
