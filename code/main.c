#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "intern.h"
#include "batch.h"

int main() {
    MYSQL_ROW row; 
    MYSQL_RES *res; 
    MYSQL_RES *result; 
    MYSQL *conn;

    char *server = ""; 
    char *user = ""; 
    char *password = ""; 
    char *database = ""; 
    
    char buffer[1024]; 
    int choice;

    int intern_id;
    char batch_code[20];
     
    conn = mysql_init(NULL); 
    if (!conn) { 
        fprintf(stderr, "Error: Failed to create MySQL connection\n"); 
        exit(1); 
    } 

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) { 
        fprintf(stderr, "Error: Failed to connect to MySQL database\n"); 
        exit(1);
    } 

    // Create BATCH_DETAILS Table
    if (mysql_query(conn, "SELECT 1 FROM BATCH_DETAILS LIMIT 1")) {
        if (mysql_query(conn, "CREATE TABLE BATCH_DETAILS (BATCH_CODE VARCHAR(20) PRIMARY KEY, COURSE_NAME VARCHAR(255) NOT NULL, CATEGORY VARCHAR(255) NOT NULL, START_DATE DATE NOT NULL, END_DATE DATE NOT NULL, TRAINER_NAME VARCHAR(255)) NOT NULL")) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
            }
    }

    // Create INTERN_DETAILS Table
    if (mysql_query(conn, "SELECT 1 FROM INTERN_DETAILS LIMIT 1")) {
            if (mysql_query(conn, "CREATE TABLE INTERN_DETAILS(ID INT AUTO_INCREMENT PRIMARY KEY, NAME VARCHAR(255) NOT NULL, COLLEGE_NAME VARCHAR(255) NOT NULL, COURSE_ID VARCHAR(20) NOT NULL, DOB DATE NOT NULL, GENDER VARCHAR(7) NOT NULL, ADDRESS VARCHAR(255) NOT NULL, PHONE_NUMBER VARCHAR(10) NOT NULL, DESCRIPTION VARCHAR(255) NOT NULL, TASK VARCHAR(255), COMPLETION_STATUS VARCHAR(12), PERFORMANCE_SCORE INT, CONSTRAINT FKRG FOREIGN KEY (COURSE_ID) REFERENCES BATCH_DETAILS(BATCH_CODE), CONSTRAINT CKG CHECK (GENDER IN ('MALE', 'FEMALE', 'OTHER')), CONSTRAINT CKPN CHECK (PHONE_NUMBER REGEXP '^[0-9]{10}&'), CONSTRAINT CKS CHECK (COMPLETION_STATUS IN ('COMPLETED', 'ONGOING')))")) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
    } 
    
    printf("**********MENU**********"); 
     
    while (1) {
        printf("\n0. Check connection"); 
        printf("\n1. Insert Intern Details"); 
        printf("\n2. Edit Details of an Intern"); 
        printf("\n3. Delete Details of an Intern"); 
        printf("\n4. Add/Edit Intern's Performance Details"); 
        printf("\n5. Insert New Batch Details");
        printf("\n6. Edit New Batch Details");
        printf("\n7. Delete a Batch's Details");
        printf("\n8. Display list of all batches");
        printf("\n9. Display Batch Details");
        printf("\n10. Display Intern's Performance");
        printf("\n11. Exit"); 
        printf("\n\nEnter your choice: "); 

        if (!fgets(buffer, 1024, stdin))
        {
            return 1; // reading input failed, give up
        }

        choice = atoi(buffer); // received input, convert it to integer
         
        switch (choice) {
            case 0:
                CheckConnection(conn); 
            case 1:                 
                AddInternDetails();
                break; 
            case 2:
                EditInternDetailsUsingID();
                break; 
            case 3:
                DeleteInternDetailsByID(); 
                break; 
            case 4:             
                EditInternPerformanceDetails(); 
                break;
            case 5:
                AddBatchDetails(); 
                break; 
            case 6:
                EditBatchDetailsUsingID(); 
                break; 
            case 7:
                DeleteBatchDetailsByID(); 
                break; 
            case 8:
  		        DisplayListOfBatches(); 
                break;
 		    case 9:	   
                DisplayBatchDetails();
                break;
            case 10:
                DisplayInternPerformance();
                break;
            case 11: 
                mysql_close(conn);               
                exit(1);                 
                break; 

            default: 
                printf("\nInvalid Choice. Please Enter Again: "); 
        } 
    } 
}
