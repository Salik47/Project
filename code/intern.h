#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

MYSQL_ROW row; 
MYSQL_RES *res; 
MYSQL_RES *temp_res; 
MYSQL_RES *result; 
MYSQL *conn1;

char *server = ""; 
char *user = ""; 
char *password = ""; 
char *database = ""; 

conn1 = mysql_init(NULL); 

if (!conn1) { 
    fprintf(stderr, "Error: Failed to create MySQL connection\n"); 
    exit(1); 
} 

if (!mysql_real_connect(conn1, server, user, password, database, 0, NULL, 0)) { 
    fprintf(stderr, "Error: Failed to connect to MySQL database\n"); 
    exit(1);
}

struct Intern {
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

int intern_id;

void AddInternDetails() {
    char query[500];

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

    sprintf(query,
            "INSERT INTO INTERN_DETAILS(NAME, COLLEGE_NAME, COURSE_ID, DOB, GENDER, ADDRESS, PHONE_NUMBER, DESCRIPTION) VALUES ('%s','%s','%s','%s','%s','%s','%s','%s')",
            name, college, course, date_of_birth, gender, address, phone_number, description);

    if (mysql_query(conn1, query))
    {
        fprintf(stderr, "Error: Failed to insert course into MySQL database\n");
        mysql_close(conn1);
        exit(1);
    }
    printf("\nIntern details added successfully");
}

void EditInternDetailsUsingID() {
    char query[500];
    char temp_query[500];
    struct Intern i2;
    char local_buffer[1024];

    printf("\nEnter the ID of intern: "); 
    if (!fgets(local_buffer, 1024, stdin))
    {
        return 1; // reading input failed, give up
    }

    intern_id = atoi(local_buffer); // received input, convert it to integer 

    sprintf(temp_query, "SELECT * FROM INTERN_DETAILS WHERE ID=%d", intern_id);

    if (mysql_query(conn1, temp_query)) {
            fprintf(stderr, "Error: failed to execute query (%s)\n", mysql_error(conn1));
            mysql_close(conn1);
            exit(1);
        }

    temp_res = mysql_store_result(conn1);
    if (!temp_res) {
        fprintf(stderr, "Error: failed to store query result (%s)\n", mysql_error(conn1));
        mysql_close(conn1);
        exit(1);
    }

    if (mysql_num_rows(temp_res) == 0) {
        printf("\nNo intern with ID = %d exists", intern_id);
        return;
    }
        
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
        

    sprintf(query,"UPDATE INTERN_DETAILS NAME='%s', COLLEGE='%s', COURSE_ID='%s', DOB='%s', GENDER='%s', ADDRESS='%s', PHONE_NUMBER='%s', DESCRIPTION='%s' where ID='%d",
                        name, college, course, date_of_birth, gender, address, phone_number, description, intern_id);

    if(mysql_query(conn1, query)) {
        fprintf(stderr, "\nError: Failed to update the record with id = %d in intern table table", intern_id);
        mysql_close(conn1);
        exit(1);
    }
    printf("\nIntern details updated successfully");
}

void DeleteInternDetailsByID() {
    char query[500];
    char temp_query[500];
    char local_buffer[1024];

    printf("\nEnter the ID of intern: "); 
    if (!fgets(local_buffer, 1024, stdin))
    {
        return 1; // reading input failed, give up
    }

    intern_id = atoi(local_buffer); // received input, convert it to integer 

    sprintf(temp_query, "SELECT * FROM INTERN_DETAILS WHERE ID=%d", intern_id);

    if (mysql_query(conn1, temp_query)) {
            fprintf(stderr, "Error: failed to execute query (%s)\n", mysql_error(conn1));
            mysql_close(conn1);
            exit(1);
        }

    temp_res = mysql_store_result(conn1);
    if (!temp_res) {
        fprintf(stderr, "Error: failed to store query result (%s)\n", mysql_error(conn1));
        mysql_close(conn1);
        exit(1);
    }

    if (mysql_num_rows(temp_res) == 0) {
        printf("\nNo intern with ID = %d exists", intern_id);
        return;
    }    

    sprintf(query, "DELETE FROM INTERN_DETAILS WHERE ID='%d'", intern_id);

    if(mysql_query(conn1, query)) {
        fprintf(stderr, "\nError:Failed to delete the record from Batch table");
        mysql_close(conn1);
        exit(1);
    }

    printf("\nIntern details deleted successfully");
}

void EditInternPerformanceDetails() {
    char query[500];
    char temp_query[500];
    char local_buffer[1024];

    printf("\nEnter the ID of intern: "); 
    if (!fgets(local_buffer, 1024, stdin))
    {
        return 1; // reading input failed, give up
    }

    intern_id = atoi(local_buffer); // received input, convert it to integer 

    sprintf(temp_query, "SELECT * FROM INTERN_DETAILS WHERE ID=%d", intern_id);

    if (mysql_query(conn1, temp_query)) {
            fprintf(stderr, "Error: failed to execute query (%s)\n", mysql_error(conn1));
            mysql_close(conn1);
            exit(1);
        }

    temp_res = mysql_store_result(conn1);
    if (!temp_res) {
        fprintf(stderr, "Error: failed to store query result (%s)\n", mysql_error(conn1));
        mysql_close(conn1);
        exit(1);
    }

    if (mysql_num_rows(temp_res) == 0) {
        printf("\nNo intern with ID = %d exists", intern_id);
        return;
    } 

    struct InternPerformance iper; 
        
    printf("Enter task: "); 
    fgets(iper.task, sizeof(iper.task), stdin); 
        
    printf("Enter status: "); 
    fgets(iper.status, sizeof(iper.status), stdin); 
        
    printf("Enter intern's performance score: "); 
    scanf("%d", &iper.perf_score); 

    sprintf(query,"UPDATE INTERN_DETAILS TASK='%s', PERFORMANCE_SCORE='%d', COMPLETION_STATUS='%s' where ID ='%d", task, performance_score, status, intern_id);

    if(mysql_query(conn1, query)) {
        fprintf(stderr, "\nError: Failed to update the record with id = %d in intern table table", intern_id);
        mysql_close(conn1);
        exit(1);
    }
    printf("\nIntern performance details updated successfully");
}

void DisplayInternPerformance() {
    char query[500];
    char temp_query[500];
    char local_buffer[1024];

    printf("\nEnter the ID of intern: "); 
    if (!fgets(local_buffer, 1024, stdin))
    {
        return 1; // reading input failed, give up
    }

    intern_id = atoi(local_buffer); // received input, convert it to integer 

    sprintf(temp_query, "SELECT * FROM INTERN_DETAILS WHERE ID=%d", intern_id);

    if (mysql_query(conn1, temp_query)) {
            fprintf(stderr, "Error: failed to execute query (%s)\n", mysql_error(conn1));
            mysql_close(conn1);
            exit(1);
        }

    temp_res = mysql_store_result(conn1);
    if (!temp_res) {
        fprintf(stderr, "Error: failed to store query result (%s)\n", mysql_error(conn1));
        mysql_close(conn1);
        exit(1);
    }

    if (mysql_num_rows(temp_res) == 0) {
        printf("\nNo intern with ID = %d exists", intern_id);
        return;
    }

    sprintf(query, "select ID, NAME, TASK, STATUS, PERFORMANCE_SCORE from INTERN_DETAILS where ID='%d'", intern_id);

    if(mysql_query(conn1, query)){
        fprintf(stderr,"%s\n",mysql_error(conn1));
        exit(1);
    }

    MYSQL_RES *result = mysql_use_result(conn1);
    MYSQL_ROW row;

    printf("Intern's Performance Details:\n");

    while((row=mysql_fetch_row(result))!=NULL){
        printf("Id: %s\n",row[0]);
        printf("Name: %s\n",row[1]);
        printf("Task: %s\n",row[9]);
        printf("Status: %s\n",row[10]);
        printf("Score: %s\n",row[11]);
    }
}

mysql_close(conn1);