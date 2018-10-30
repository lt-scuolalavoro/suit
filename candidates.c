#include "stdio.h"
#include "string.h"
#include "stdlib.h"

struct candidate {
  //declaration of the structure variables
  int id;
  //Name and surname must be a maximum of 20 characters
  char firstName[20];
  char lastName[20];
  int age;
  float salary;
};
  //declaration function

  //this function, given in input a FILE, returns its number of lines;
int findLines(FILE *);
  //this function, given in input lastName, the struct of the candidates and the numbers of the candidates, returns the age of the person;
char age(char [],struct candidate *dip,int numDip);


void main(){
  //Database file must be in the same directory level;
  FILE *fp;
  fp = fopen("database.txt","r");
  int numDip = findLines(fp);

  int i;

  //declaration that defines a physically grouped list of variables;
  struct candidate dip[numDip];
  //rewind function sets the file position to the beginning of the file of the given stream;
  rewind(fp);

  for(i=0;i<numDip;i++){
    //the function fscanf reads formatted input from a stream;
    fscanf(fp,"%i %s %s %i %f",&dip[i].id, dip[i].firstName, dip[i].lastName, &dip[i].age, &dip[i].salary);
  }
  printf("%i\n",dip[6].age);

  char appoggio[50];
  printf("lastName: ");
  scanf("%s",appoggio);
  printf("Age : %i\n",age(appoggio,dip,numDip));

  fclose(fp);
}

char age(char appoggio[],struct candidate *dip, int numDip){
  int trovato = 0;
  for(int i=0;i<numDip;i++){
    //the function strcmp compares the string pointed to, by str1 to the string pointed to by str2;
    if(strcmp(appoggio,dip[i].lastName)==0){
      trovato = 1;
      return dip[i].age;
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
