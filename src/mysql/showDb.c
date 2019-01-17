#include "../lib/mysql_utils.h"

int main(int argc, char **argv){      
  setupDb("localhost", "root", NULL, "suit");
  
  executeQuery("SELECT * FROM Candidate", "Operation completed successfully", "SELECT");
  
  MYSQL_RES *result = mysql_store_result(con);
  
  if (result == NULL){
      finishWithError(con);
  }

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  
  while ((row = mysql_fetch_row(result))) 
  { 
      for(int i = 0; i < num_fields; i++) 
      { 
          printf("%s ", row[i] ? row[i] : "NULL"); 
      } 
          printf("\n"); 
  }
  
  mysql_free_result(result);
  
  closeProgram();
}
