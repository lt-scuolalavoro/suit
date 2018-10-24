#include "stdio.h"
#include "string.h"
#include "stdlib.h"

struct candidate {
  int id;
  char firstName[20];
  char lastName[20];
  int age;
  float salary;
};

int findLines(FILE *);

char age(char [],struct candidate *dip,int numDip);

void main(){
  //Database file must be in the same directory level
  FILE *fp;
  fp = fopen("database.txt","r");
  int numDip = findLines(fp);

  struct candidate dip[numDip];
  int i;

  rewind(fp);
  for(i=0;i<numDip;i++){
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

  while(fgets(ch, sizeof(ch), fp) != NULL){
        lines++;
    }
  return lines;
}
