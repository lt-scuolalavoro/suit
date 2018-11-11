#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"

struct candidate {
  //declaration of the structure variables
  int id;
  //Name and surname must be a maximum of 20 characters
  char firstName[20];
  char lastName[20];
  char birthDate[11]; //array must be of 11 chars to accomodate for the \0 terminator.
  bool employed;
  float salary;
};
//declaration function

//this function, given in input a FILE, returns its number of lines;
int evaluateEntriesNumber(FILE *);
//this function, given in input lastName, the struct of the candidates and the numbers of the candidates, returns the age of the person;
char * age(char [], struct candidate *cand, int nCandidates);
void convertDbToCsv(char *, int , struct candidate[]);

void main(){
  //Database file must be in the same directory level;
  FILE *fp;
  char filename[30] = "database.txt";
  fp = fopen(filename, "r+");
  int nCandidates = evaluateEntriesNumber(fp);
  int i;
  //declaration that defines a physically grouped list of variables;
  struct candidate cand[nCandidates];

  //Set the file position to the beginning of fp;
  rewind(fp);
  for(i=0; i<nCandidates; i++){
    //Read CSV text file;
    fscanf(fp, "%d,%[^,],%[^,],%[^,],%d", &cand[i].id, cand[i].firstName, cand[i].lastName, cand[i].birthDate, &cand[i].employed);
  }

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

int evaluateEntriesNumber(FILE *fp){
  char ch[100];
  int lines=0;
  int num=0;
  //while the lines is not NULL increase the counter variable;
  while(fgets(ch, sizeof(ch), fp) != NULL){
    lines++;
  }
  return lines;
}

void convertDbToCsv(char *filename, int nCand, struct candidate cand[]){
  FILE *fp;
  fp = fopen(filename, "w");
  for (int i = 0; i < nCand; ++i){
    fprintf(fp, "%d,%s,%s,%s,%d\n", cand[i].id, cand[i].firstName, cand[i].lastName, cand[i].birthDate, cand[i].employed);
  }
  fclose(fp);
}
