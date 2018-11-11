#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"

struct candidate {
//declaration of the structure variables
    bool removed;
    int id;
  //Name and surname must be a maximum of 20 characters
    char firstName[20];
    char lastName[20];
    char birthDate[11]; //array must be of 11 chars to accomodate for the \0 terminator.
    bool employed;
    float salary;
};
//Functions declaration
//this function, given in input a FILE, returns its number of lines;
int evaluateEntriesNumber(FILE *);
//this function, given in input lastName, the struct of the candidates and the numbers of the candidates, returns the age of the person;
char * age(char [], struct candidate *cand, int nCandidates);
void convertDbToCsv(char *, int , struct candidate[]);
int addNewCandidate(FILE *, struct candidate *, int);

void main(){
  //Database file must be in the same directory level;
  FILE *fp;
  char filename[30] = "database.txt";
  fp = fopen(filename, "a+");
  int nCandidates = evaluateEntriesNumber(fp);
  int choice;
  int i, nCandVisualized;
  char lastName[20];
  int found;
  char choice2;
  //Create dynamic array
  struct candidate * cand = malloc(nCandidates * sizeof(struct candidate));

  //Set the file position to the beginning of fp;
  rewind(fp);
  for(i=0; i<nCandidates; i++){
    //Read CSV text file;
    fscanf(fp, "%d,%d,%[^,],%[^,],%[^,],%d,%f", &cand[i].removed, &cand[i].id, cand[i].firstName, cand[i].lastName, cand[i].birthDate, &cand[i].employed, &cand[i].salary);
  }
  do {
    printf("1. Print candidates;\n2. Print deleted candidates;\n3. Search candidate by last name;\n4. Add candidate;\n5. Remove candidate.\n");
  do {
    printf("Insert: ");
    scanf("%d", &choice);
    if (choice<1||choice>5) {
        printf("Invalid value.\n");
    }
  } while (choice<1||choice>5);
  printf("\n");
  switch(choice) {
  case 1:
    nCandVisualized=0;
    for (i=0; i<nCandidates; i++) {
        if (cand[i].removed==0) {
            printCandidate(cand, i);
            nCandVisualized++;
        }
    }
    if (nCandVisualized==0) {
        printf("No candidates found.\n");
    }
    break;
  case 2:
    nCandVisualized=0;
    for (i=0; i<nCandidates; i++) {
        if (cand[i].removed==1) {
            printCandidate(cand, i);
            nCandVisualized++;
        }
    }
    if (nCandVisualized==0) {
        printf("No deleted candidates found.\n");
    }
    break;
  case 3:
    printf("Last name: ");
    scanf("%s", lastName);
    found=0;
    for (i=0; i<nCandidates; i++) {
        if (strcmp(lastName, cand[i].lastName)==0) {
            if (cand[i].removed==0) {
                found=1;
                printCandidate(cand, i);
            }
        }
    }
    if (found==0) {
        printf("No candidate found with last name: %s", lastName);
    }
    break;
  case 4:
    nCandidates = addNewCandidate(fp, cand, nCandidates);
    break;
  case 5:
    found=0;
    printf("Last name: ");
    scanf("%s", lastName);
    for (i=0; i<nCandidates; i++) {
        if (strcmp(lastName, cand[i].lastName)==0) {
            found=1;
            removeCandidate(cand, i);
        }
    }
    break;
  }
    do {
        printf("\nContinue? [y,n] ");
        scanf(" %c", &choice2);
        if (choice2 != 'y' && choice2!= 'n') {
            printf("Invalid value.");
        }
    } while (choice2 != 'y' && choice2!= 'n');
} while (choice2=='y');

  free(cand);
  fclose(fp);
}

char * age(char temp[], struct candidate *cand, int nCandidates){
  int found = 0;
  for(int i=0; i<nCandidates; i++){
    //the function strcmp compares the string pointed to, by str1 to the string pointed to by str2;
    if(strcmp(temp, cand[i].lastName)==0){
      found = 1;
      return cand[i].birthDate;
    }
  }
}
void refreshDocument(FILE *fp, struct candidate *cand, int nCand) {

}
void printCandidate(struct candidate *cand, int i) {
    if (cand[i].employed==1) {
        printf("%s %s %s %d %f", cand[i].firstName, cand[i].lastName, cand[i].birthDate, cand[i].employed, cand[i].salary);
    } else {
        printf("%s %s %s", cand[i].firstName, cand[i].lastName, cand[i].birthDate);
    }
    printf("\n");
}
void removeCandidate(struct candidate *cand, int i) {
    cand[i].removed=1;
}
int evaluateEntriesNumber(FILE *fp){
  char ch[100];
  int lines=0;
  int num=0;
  rewind(fp);
  //while the lines is not NULL increase the counter variable;
  while(fgets(ch, sizeof(ch), fp) != NULL){
    lines++;
  }
  return lines;
}
//Print the struct array on the text file, each field separated by commas 
void convertDbToCsv(char *filename, int nCand, struct candidate cand[]){
  FILE *fp;
  fp = fopen(filename, "w");
  for (int i = 0; i < nCand; ++i){
    fprintf(fp, "%d,%s,%s,%s,%d\n", cand[i].id, cand[i].firstName, cand[i].lastName, cand[i].birthDate, cand[i].employed);
  }
  fclose(fp);
}
//Add a new candidate to the struct array, print on the txt file the last element of the struct and return the updated number of entries
int addNewCandidate(FILE *fp, struct candidate *cand, int nCand){
  nCand++;
  //Resize the array
  cand = realloc(cand, nCand * sizeof(struct candidate));
  int i = nCand-1;  //Last position of the array
  cand[i].id = nCand;
  printf("First name: ");
  scanf("%s", cand[i].firstName);
  printf("Last name: ");
  scanf("%s", cand[i].lastName);
  printf("Birth date: ");
  scanf("%s", cand[i].birthDate);
  char choice;
  do{
    printf("Is the candidate employed? [y/n] ");
    scanf(" %c", &choice);
    if(choice=='y'){
      cand[i].employed = 1;
      printf("Salary: ");
      scanf("%f", &cand[i].salary);
      fprintf(fp, "\n%d,%d,%s,%s,%s,%d,%.2f", 0, cand[i].id, cand[i].firstName, cand[i].lastName, cand[i].birthDate, cand[i].employed, cand[i].salary);
    }else if (choice=='n'){
      cand[i].employed = 0;
      fprintf(fp, "\n%d,%d,%s,%s,%s,%d", 0, cand[i].id, cand[i].firstName, cand[i].lastName, cand[i].birthDate, cand[i].employed);
    }else{
      printf("Invalid value\n");
    }
  }while(choice != 'y' && choice != 'n');
  //Print on file
  rewind(fp);
  return nCand;
}
