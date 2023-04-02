#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <intern.h>
#include <batch.h>
MYSQL *conn;

struct Intern(){
    char name[100]; 
    char college[255]; 
    char course[20]; 
    char date_of_birth[20]; 
    char gender[7]; 
    char address[255]; 
    char phone_number[10]; 
    char description[255];
};

struct InternPerformance {
    char task[100]; 
    char status[30]; 
    int perf_score; 
};

struct Batch(){
    char batch_id[20]; 
    char course_name[50]; 
    char category[50]; 
    char start_date[20];     
    char end_date[20]; 
    char trainer_name[100]; 
};

int main() {
    MYSQL_ROW row; 
    MYSQL_RES *res; 
    MYSQL_RES *result; 

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
            case 1:             
                struct Intern i;

                printf("\nEnter the name of the intern: "); 
                fgets(i.name, sizeof(i.name), stdin);
                 
                printf("\nEnter the college of the intern: "); 
                fgets(i.college, sizeof(i.college), stdin);
                 
                printf("\nEnter the course of the intern: "); 
                fgets(i.course, sizeof(i.course), stdin); 


                printf("\nEnter the DOB of the intern (in YYYY-MM-DD format): "); 
                fgets(i.date_of_birth, sizeof(i.date_of_birth), stdin); 

                printf("\nEnter the gender of the intern: "); 
                fgets(i.gender, sizeof(i.gender), stdin); 
                 
                printf("\nEnter the address of the intern: "); 
                fgets(i.address, sizeof(i.address), stdin); 

                printf("\nEnter the mobile number of the intern: "); 
                fgets(i.phone_number, sizeof(i.phone_number), stdin); 
                 
                printf("\nEnter the description of the intern: "); 
                fgets(i.description, sizeof(i.description), stdin); 
                 
                AddInternDetails(conn, i.name, i.college, i.course, i.date_of_birth, i.gender, i.address, i.phone_number, i.description);
                break; 

            case 2:
                struct Intern i2;

                printf("\nEnter the ID of intern: "); 
                scanf("%d", &intern_id); 
                 
                printf("\nEnter the name of the intern: "); 
                fgets(i2.name, sizeof(i2.name), stdin);
                 
                printf("\nEnter the college of the intern: "); 
                fgets(i2.college, sizeof(i2.college), stdin);
                 
                printf("\nEnter the course of the intern: "); 
                fgets(i2.course, sizeof(i2.course), stdin); 

                printf("\nEnter the DOB of the intern (in YYYY-MM-DD format): "); 
                fgets(i2.date_of_birth, sizeof(i2.date_of_birth), stdin); 
                 
                printf("\nEnter the gender of the intern: "); 
                fgets(i2.gender, sizeof(i2.gender), stdin); 
                 
                printf("\nEnter the address of the intern: "); 
                fgets(i2.address, sizeof(i2.address), stdin); 

                printf("\nEnter the mobile number of the intern: "); 
                fgets(i2.phone_number, sizeof(i2.phone_number), stdin); 
                 
                printf("\nEnter the description of the intern: "); 
                fgets(i2.description, sizeof(i2.description), stdin); 
                 
                EditInternDetails(conn, intern_id, i2.name, i2.college, i2.course, i2.date_of_birth, i2.gender, i2.address, i2.phone_number, i2.description);
                break; 

            case 3: 
                printf("\nEnter the ID of intern: "); 
                scanf("%d", &intern_id); 

                DeleteInternDetailsById(conn, intern_id); 
                break; 

            case 4: 
                struct InternPerformance iper;

                printf("\nEnter the Intern's id"); 
                scanf("%d", &intern_id); 
                 
                printf("Enter task: "); 
                fgets(iper.task, sizeof(iper.task), stdin); 
                 
                printf("Enter status: "); 
                fgets(iper.status, sizeof(iper.status), stdin); 
                 
                printf("Enter intern's performance score: "); 
                scanf("%d", &iper.performance_score); 

                 
                EditInternPerformanceDetails(conn, intern_id, iper.task, iper.performance_score, iper.status); 
                break;

            case 5:
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
  
                AddBatchDetails(conn, b.batch_id , b.course_name, b.category, b.start_date, b.end_date, b.trainer_name); 
                break; 

            case 6:

                struct Batch b2;

                printf("\nEnter the batch id: ");
                fgets(b2.batch_id, sizeof(b2.batch_id), stdin); 

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
  
                EditBatchDetailsUsingID(conn, b2.batch_id , b2.course_name, b2.category, b2.start_date, b2.end_date, b2.trainer_name); 
                break; 

            case 7:
                printf("\nEnter the batch id: ");
                fgets(batch_code, sizeof(batch_code), stdin); 

                DeleteBatchDetailsByID(conn, batch_code); 
                break; 

            case 8:
  		        DisplayListOfBatches(conn); 
                break;

 		    case 9:	   
                struct Batch b;

                printf("\nEnter the batch id: ");
                fgets(batch_code, sizeof(batch_code), stdin);  

                DisplayBatchDetails(conn, batch_code)
                break;

            case 10:
                printf("\nEnter Intern's ID: ");
                scanf("%d", &intern_id);
                DisplayInternPerformance(conn, intern_id);
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
