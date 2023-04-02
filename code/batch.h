#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
// MYSQL *conn;

void CheckConnection(MYSQL *conn) {
    if (conn == NULL) {
        fprintf(stderr, "Error: Failed to connect to MySQL database\n");
        exit(1);
    }

    printf("%s", mysql_get_host_info(conn));
}

void AddBatchDetails(
    MYSQL *conn,
    char batch_id[20],
    char course_name[255],
    char category[255],
    char start_date[20],
    char end_date[20],
    char trainer_name[255]) {
        char query[500];
        sprintf(query, "INSERT INTO BATCH_DETAILS(BATCH_CODE, COURSE_ID, CATEGORY, START_DATE, END_DATE, TRAINER_NAME) VALUES ('%s', '%s','%s','%s','%s','%s')", batch_id, course_name, category, start_date, end_date, trainer_name);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "Error: Failed to insert batch into MySQL database\n");
            mysql_close(conn);
            exit(1);
        }

        printf("\nBatch details added successfully");
}

void EditBatchDetailsUsingID(
    MYSQL *conn,
    char batch_id[20],
    char course_name[255],
    char category[255],
    char start_date[20],
    char end_date[20],
    char trainer_name[255]) {
        char query[500];
        printf("7");
        sprintf(query,"UPDATE BATCH_DETAILS COURSE_ID='%s', CATEGORY='%s', START_DATE='%s', END_DATE='%s', TRAINER_NAME='%s' where BATCH_CODE ='%s", course_name, category, start_date, end_date, trainer_name, batch_id);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "\nError: Failed to update the record with id = %s in batch table", batch_id);
            mysql_close(conn);
            exit(1);
        }

        printf("\nIntern details updated successfully");
}

void DeleteBatchDetailsByID(MYSQL *conn, char batch_id[20]) {
    char query[500];
    printf("8");
    sprintf(query, "DELETE FROM BATCH_DETAILS WHERE BATCH_CODE='%s'", batch_id);

    if(mysql_query(conn, query)) {
        fprintf(stderr, "\nError:Failed to delete the record from Batch table");
        mysql_close(conn);
        exit(1);
    }

    printf("\nBatch details deleted successfully");
}

void DisplayListOfBatches(MYSQL *conn){
    char query[500];
   printf("9");
    sprintf(query, "SELECT BATCH_CODE,COURSE_NAME from Batch_Details");

    if(mysql_query(conn, query)){
        fprintf(stderr,"%s\n",mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);

  if (result == NULL) {
      fprintf(stderr,"%s\n",mysql_error(conn));
      exit(1);
  }

 /* int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;

  while ((row = mysql_fetch_row(result)))
  {
      for(int i = 0; i < num_fields; i++)
      {
          if (i == 0)
          {
             while(field = mysql_fetch_field(result))
             {
                printf("%s ", field->name);
             }

             printf("\n");
          }

          printf("%s  ", row[i] ? row[i] : "NULL");
      }
  }

  mysql_free_result(result);
  printf("\n");*/

  MYSQL_ROW row;

  printf("Batch details are\n");

  while((row=mysql_fetch_row(result))!=NULL){

        printf("Id: '%s\t'Batch Name: '%s\n'", row[0], row[1]);
  }

}

void DisplayBatchDetails(MYSQL *conn, char batch_id[20]){
    char query[500];
    printf("10");
    sprintf(query, "SELECT NAME FROM INTERN_DETAILS WHERE COURSE_ID='%s'", batch_id);

    if(mysql_query(conn, query)){
        fprintf(stderr,"%s\n",mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;

    printf("Batch Details:\n");
    printf("List of Interns in this batch:-\n");
    while((row = mysql_fetch_row(result)) != NULL){
        printf("%s\n", row[1]);
    }
}