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
  int age;
  bool employed;
  float salary;
};
//declaration function

//this function, given in input a FILE, returns its number of lines;
int findLines(FILE *);
//this function, given in input lastName, the struct of the candidates and the numbers of the candidates, returns the age of the person;
char age(char [], struct candidate *cand, int nCandidates);


void main(){
  //Database file must be in the same directory level;
  FILE *fp;
  fp = fopen("database.txt", "r");
  int nCandidates = findLines(fp);


  int i;
  //declaration that defines a physically grouped list of variables;
  struct candidate cand[nCandidates];
  //rewind function sets the file position to the beginning of the file of the given stream;
  rewind(fp);

  for(i=0; i<nCandidates; i++){
    //the function fscanf reads formatted input from a stream;
    fscanf(fp, "%i %s %s %i %d", &cand[i].id, cand[i].firstName, cand[i].lastName, &cand[i].age, &cand[i].employed);
  }

  char temp[50];
  printf("lastName: ");
  scanf("%s", temp);
  printf("Age : %i\n", age(temp,cand,nCandidates));

  fclose(fp);
}

char age(char temp[], struct candidate *cand, int nCandidates){
  int found = 0;
  for(int i=0; i<nCandidates; i++){
    //the function strcmp compares the string pointed to, by str1 to the string pointed to by str2;
    if(strcmp(temp, cand[i].lastName)==0){
      found = 1;
      return cand[i].age;
    }
  }
}

int findLines(FILE *fp){
  char ch[100];
  int lines=0;
  int num=0;
  //while the lines is not NULL increase the counter variable;
  while(fgets(ch, sizeof(ch), fp) != NULL){
    lines++;
  }
  return lines;
}
