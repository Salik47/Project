#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

MYSQL_ROW row; 
MYSQL_RES *res; 
MYSQL_RES *result; 
MYSQL_RES *temp_res; 
MYSQL *conn2;

char *server = ""; 
char *user = ""; 
char *password = ""; 
char *database = ""; 

conn2 = mysql_init(NULL); 

if (!conn2) { 
    fprintf(stderr, "Error: Failed to create MySQL connection\n"); 
    exit(1); 
} 

if (!mysql_real_connect(conn2, server, user, password, database, 0, NULL, 0)) { 
    fprintf(stderr, "Error: Failed to connect to MySQL database\n"); 
    exit(1);
}

struct Batch {
    char batch_id[20]; 
    char course_name[50]; 
    char category[50]; 
    char start_date[20];     
    char end_date[20]; 
    char trainer_name[100]; 
};

void CheckConnection(MYSQL *conn2) {
    if (conn2 == NULL) {
        fprintf(stderr, "Error: Failed to connect to MySQL database\n");
        exit(1);
    }

    printf("%s", mysql_get_host_info(conn2));
}

void AddBatchDetails(){
    char query[500];
    struct Batch b;

    printf("\nEnter the batch id: ");
    fgets(b.batch_id, sizeof(b.batch_id), stdin); 

    printf("\nEnter the Course name: "); 
    fgets(b.course_name, sizeof(b.course_name), stdin); 

    printf("\nEnter the Category of Course: "); 
    fgets(b.category, sizeof(b.category), stdin); 

    printf("\nEnter the Start date of Batch (in YYYY-MM-DD format): "); 
    fgets(b.start_date, sizeof(b.start_date), stdin); 

    printf("\nEnter the End date of Batch (in YYYY-MM-DD format): "); 
    fgets(b.end_date, sizeof(b.end_date), stdin); 

    printf("\nEnter the Trainer's name: "); 
    fgets(b.trainer_name, sizeof(b.trainer_name), stdin); 

    sprintf(query, "INSERT INTO BATCH_DETAILS(BATCH_CODE, COURSE_ID, CATEGORY, START_DATE, END_DATE, TRAINER_NAME) VALUES ('%s', '%s','%s','%s','%s','%s')", batch_id, course_name, category, start_date, end_date, trainer_name);

    if (mysql_query(conn2, query)) {
    fprintf(stderr, "Error: Failed to insert batch into MySQL database\n");
    mysql_close(conn2);
    exit(1);
    }

    printf("\nBatch details added successfully");
}

void EditBatchDetailsUsingID() {
    char query[500];
    char temp_query[500];
    char batch_code[20];

    printf("\nEnter the batch id: ");
    fgets(batch_code, sizeof(batch_code), batch_code); 

    sprintf(temp_query, "SELECT * FROM BATCH_DETAILS WHERE BATCH_CODE=%s", batch_code);

    if (mysql_query(conn2, temp_query)) {
        fprintf(stderr, "Error: failed to execute query (%s)\n", mysql_error(conn2));
        mysql_close(conn2);
        exit(1);
    }

    temp_res = mysql_store_result(conn2);

    if (!temp_res) {
        fprintf(stderr, "Error: failed to store query result (%s)\n", mysql_error(conn2));
        mysql_close(conn2);
        exit(1);
    }

    if (mysql_num_rows(temp_res) == 0) {
        printf("\nNo intern with ID = %d exists", intern_id);
        return;
    }

    struct Batch b2;
    b2.batch_id = batch_code;

    printf("\nEnter the Course name: "); 
    fgets(b2.course_name, sizeof(b2.course_name), stdin); 

    printf("\nEnter the Category of Course: "); 
    fgets(b2.category, sizeof(b2.category), stdin);

    printf("\nEnter the Start date of Batch (in YYYY-MM-DD format): "); 
    fgets(b2.start_date, sizeof(b2.start_date), stdin); 

    printf("\nEnter the End date of Batch (in YYYY-MM-DD format): "); 
    fgets(b2.end_date, sizeof(b2.end_date), stdin); 

    printf("\nEnter the Trainer's name: "); 
    fgets(b2.trainer_name, sizeof(b2.trainer_name), stdin);

    sprintf(query,"UPDATE BATCH_DETAILS COURSE_ID='%s', CATEGORY='%s', START_DATE='%s', END_DATE='%s', TRAINER_NAME='%s' where BATCH_CODE ='%s", course_name, category, start_date, end_date, trainer_name, batch_id);

    if (mysql_query(conn2, query)) {
        fprintf(stderr, "\nError: Failed to update the record with id = %s in batch table", batch_id);
        mysql_close(conn2);
        exit(1);
    }

    printf("\nIntern details updated successfully");
}

void DeleteBatchDetailsByID() {
    char query[500];
    char query[500];
    char temp_query[500];
    char batch_code[20];

    printf("\nEnter the batch id: ");
    fgets(batch_code, sizeof(batch_code), batch_code); 

    sprintf(temp_query, "SELECT * FROM BATCH_DETAILS WHERE BATCH_CODE=%s", batch_code);

    if (mysql_query(conn2, temp_query)) {
        fprintf(stderr, "Error: failed to execute query (%s)\n", mysql_error(conn2));
        mysql_close(conn2);
        exit(1);
    }

    temp_res = mysql_store_result(conn2);

    if (!temp_res) {
        fprintf(stderr, "Error: failed to store query result (%s)\n", mysql_error(conn2));
        mysql_close(conn2);
        exit(1);
    }

    if (mysql_num_rows(temp_res) == 0) {
        printf("\nNo intern with ID = %d exists", intern_id);
        return;
    }

    sprintf(query, "DELETE FROM BATCH_DETAILS WHERE BATCH_CODE='%s'", batch_id);

    if(mysql_query(conn2, query)) {
        fprintf(stderr, "\nError:Failed to delete the record from Batch table");
        mysql_close(conn2);
        exit(1);
    }

    printf("\nBatch details deleted successfully");
}

void DisplayListOfBatches() {
    char query[500];

    sprintf(query, "SELECT BATCH_CODE, COURSE_NAME from Batch_Details");

    if(mysql_query(conn2, query)){
        fprintf(stderr,"%s\n",mysql_error(conn2));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn2);

  if (result == NULL) {
      fprintf(stderr,"%s\n",mysql_error(conn2));
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

void DisplayBatchDetails() {
    char query[500];
    char temp_query[500];
    char batch_code[20];

    printf("\nEnter the batch id: ");
    fgets(batch_code, sizeof(batch_code), batch_code); 

    sprintf(temp_query, "SELECT * FROM BATCH_DETAILS WHERE BATCH_CODE=%s", batch_code);

    if (mysql_query(conn2, temp_query)) {
        fprintf(stderr, "Error: failed to execute query (%s)\n", mysql_error(conn2));
        mysql_close(conn2);
        exit(1);
    }

    temp_res = mysql_store_result(conn2);

    if (!temp_res) {
        fprintf(stderr, "Error: failed to store query result (%s)\n", mysql_error(conn2));
        mysql_close(conn2);
        exit(1);
    }

    if (mysql_num_rows(temp_res) == 0) {
        printf("\nNo intern with ID = %d exists", intern_id);
        return;
    }

    sprintf(query, "SELECT NAME FROM INTERN_DETAILS WHERE COURSE_ID='%s'", batch_code);

    if (mysql_query(conn2, query)) {
        fprintf(stderr,"%s\n",mysql_error(conn2));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn2);
    MYSQL_ROW row;

    printf("Batch Details:\n");
    printf("List of Interns in this batch:-\n");
    while((row = mysql_fetch_row(result)) != NULL){
        printf("%s\n", row[1]);
    }
}

mysql_close(conn2);