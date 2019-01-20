#include "str_utils.h"
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
void writeOnTextFile (FILE *, int i, struct candidate *);
int isInteger(char[]);
void printInOrder(struct candidate * , int , int);

void writeOnTextFile (FILE *fp, int i, struct candidate *candidates){
    fprintf(
        fp, "%d,%s,%s,%s,%d,%.2f,%d\n",
        candidates[i].id,
        candidates[i].firstName,
        candidates[i].lastName,
        candidates[i].birthDate,
        candidates[i].employed,
        candidates[i].salary,
        candidates[i].removed
    );
}

void updateDatabase(FILE * fp, struct candidate * candidates, int nCand, char * filename) {
    fp = fopen(filename, "r+");
    for (int i = 0; i < nCand; i++) {
        writeOnTextFile (fp, i, candidates);
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
         writeOnTextFile (fp, i, candidates);
    }
    fclose(fp);
}
// Add a new candidate to the struct array and return the updated number of entries
int addNewCandidate(char * filename, struct candidate * candidates, int nCand) {
    FILE * fp;
    char str[11];
    char * token;
    bool check = 1;
    char temp[5];
    int j;
    // Reopen the file in append mode
    fp = fopen(filename, "a");
    nCand++;
    int i = nCand - 1; // Last position of the array
    candidates[i].removed = 0;
    candidates[i].id = nCand;
    // printf("First name: ");
    // scanf(" %20[^\n]", candidates[i].firstName);
    // printf("Last name: ");
    // scanf(" %20[^\n]", candidates[i].lastName);
    printf("Birth date [dd-mm-yyyy]: ");
    scanf("%s", str);

    // Il primo token va in str
    token = strtok(str, "-");
    //  Creiamo un array di string dove inserire le date splittate
    char *strData[3];

    for (i=0 ; i<3; i++) {
        if ((strData[i] = malloc(sizeof(char) * 5)) == NULL) {
            printf("unable to allocate memory \n");
            return -1;
        }
    }
    
    /*
        10-20-1000
        10-1000-20
        20-10-1000
        20-1000-10
        1000-10-20
        1000-20-10

    */

    strcpy(strData[0], str);

    for(i = 1; i <= 2; i++) {
        token = strtok(NULL, "-");
        strcpy(strData[i], token);        
    }                        
    
    for(j = 2; j >= 0; j--){
        switch(j){
            case 0 :{
                // Controlla se è l'anno -> lo mette in strData[2]
                if(atoi(strData[j]) > 31 && strlen(strData[j]) == 4){
                    swapStr(strData[0], strData[2]);
                }
            }
            break;
            case 1:{
                // Controlla se è il giorno -> lo mette in strData[0]
                if(atoi(strData[j]) > 12 && atoi(strData[j]) < 31){
                    swapStr(strData[0], strData[1]);
                }
                // Controlla se è l'anno -> lo mette in strData[2]
                if(atoi(strData[j]) > 31 && strlen(strData[j]) == 4){
                    swapStr(strData[2], strData[1]);
                }
            }
            break;
            case 2:{
                // Controlla se è il giorno -> lo mette in strData[0]
                if(atoi(strData[j]) > 12 && atoi(strData[j]) < 31){
                    swapStr(strData[0], strData[2]);
                }
                if(strlen(strData[j]) < 4)
                    check = 0;
            }
            break;
        }
    }

    swapStr(strData[0], strData[2]);

    printf("\n");
    for(i = 0; i < 3; i++) {
        printf("%s-", strData[i]);
    }
    printf("\n");

    // j=0;
    // char str2[11] = "";
    // while( strData != NULL) {
    //    //printf( " %s", token );
    //    strcat(str2,token);
    //    if(j < 2){
    //        strcat(str2,"-");
    //    }
    //    token = strtok(NULL, "-");
    //    j = j + 1 ;
    // }
    // strcpy(candidates[i].birthDate,str2);
    char choice;
    do {
        printf("Is the candidate employed? [y/n] ");
        scanf(" %c", & choice);
        if (choice == 'y') {
            candidates[i].employed = 1;
            printf("Salary: ");
            scanf("%f", & candidates[i].salary);
            writeOnTextFile (fp, i, candidates);
        } else if (choice == 'n') {
            candidates[i].employed = 0;
            candidates[i].salary = 0.0;
             writeOnTextFile (fp, i, candidates);
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

    writeOnTextFile (fp, i, candidates);

  }
  fclose(fp);
}
int isInteger(char *input) {
    int intero=1;
    for (int i=0; i<10 && input[i] !='\0' && intero==1; i++) {
        if (input[i]<'0' || input[i] > '9') {
            intero=0;
        }
    }
    return intero;
}

void format(char* filename, int nCand, struct candidate *candidates){
  char choice[10];
  int inputConverted;
  bool exit = 1;

  do {
    printf("What would you like to do?:\n1. Separate values with comma;\n2. change data form in mySQL compatible;\n3. Exit.\n");
    do {
        printf("Insert: ");
        scanf("%s", &choice);
        inputConverted=atoi(choice);
        if ((inputConverted < 1 || inputConverted > 3) || isInteger(choice)==0) {
            printf("Invalid value.\n");
          }
    } while ((inputConverted < 1 || inputConverted > 3) || isInteger(choice)==0);


      switch (inputConverted){
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

void printInOrder(struct candidate * candidates,int removed, int nCandidates){
    char orderName[nCandidates][40];
    int orderPosition [nCandidates];
    int cont = 0;
    int i;
    for (i = 0; i < nCandidates; i++) {
        if (candidates[i].removed == removed) {
            strcpy(orderName[cont], candidates[i].firstName);
            strcpy(orderName[cont]+strlen(candidates[i].firstName), candidates[i].lastName);
            orderPosition[cont] = i;
            cont++;
        }
    }

    if (cont <= 0) {
        printf("No candidates found.\n");
    } else {
        // Sort
        int j, temp1;
        char temp[40];
        for(i=0; i<cont-1; i++){
            for(j=i+1; j<cont; j++){
                if(strcmp(orderName[i],orderName[j])>0){
                    strcpy(temp, orderName[i]);
                    strcpy(orderName[i], orderName[j]);
                    strcpy(orderName[j], temp);
                    temp1 = orderPosition[i];
                    orderPosition[i] = orderPosition[j];
                    orderPosition[j] = temp1;
                }
            }
        }

        for(i=0; i<cont; i++){
            printCandidate(candidates, orderPosition[i]);
        }
    }
}

