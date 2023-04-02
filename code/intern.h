#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
// MYSQL *conn;

void AddInternDetails(
    MYSQL *conn,
    char name[255],
    char college[255],
    char course[20],
    char date_of_birth[20],
    char gender[7],
    char address[255],
    char phone_number[10],
    char description[255]
    ) {
        printf("1");
        char query[500];
        sprintf(query,
                "INSERT INTO INTERN_DETAILS(NAME, COLLEGE_NAME, COURSE_ID, DOB, GENDER, ADDRESS, PHONE_NUMBER, DESCRIPTION) VALUES ('%s','%s','%s','%s','%s','%s','%s','%s')",
                name, college, course, date_of_birth, gender, address, phone_number, description);

        if (mysql_query(conn, query))
        {
            fprintf(stderr, "Error: Failed to insert course into MySQL database\n");
            mysql_close(conn);
            exit(1);
        }
    printf("\nIntern details added successfully");
}

void EditInternDetailsUsingID(
        MYSQL *conn,
    int intern_id,
    char name[255],
    char college[255],
    char course[20],
    char date_of_birth[20],
    char gender[7],
    char address[255],
    char phone_number[10],
    char description[255]
    ) {
    printf("2");
    char query[500];
    sprintf(query,"UPDATE INTERN_DETAILS NAME='%s', COLLEGE='%s', COURSE_ID='%s', DOB='%s', GENDER='%s', ADDRESS='%s', PHONE_NUMBER='%s', DESCRIPTION='%s' where ID='%d",
                        name, college, course, date_of_birth, gender, address, phone_number, description, intern_id);

    if(mysql_query(conn, query)) {
        fprintf(stderr, "\nError: Failed to update the record with id = %d in intern table table", intern_id);
        mysql_close(conn);
        exit(1);
    }
    printf("\nIntern details updated successfully");
}

void DeleteInternDetailsByID(MYSQL *conn, int intern_id) {
    char query[500];
    printf("3");
    sprintf(query, "DELETE FROM INTERN_DETAILS WHERE ID='%d'", intern_id);

    if(mysql_query(conn, query)) {
        fprintf(stderr, "\nError:Failed to delete the record from Batch table");
        mysql_close(conn);
        exit(1);
    }

    printf("\nIntern details deleted successfully");
}

void EditInternPerformanceDetails(MYSQL *conn, int intern_id, char task[255], int performance_score, char status[12]) {
    char query[500];
    printf("4");
    sprintf(query,"UPDATE INTERN_DETAILS TASK='%s', PERFORMANCE_SCORE='%d', COMPLETION_STATUS='%s' where ID ='%d", task, performance_score, status, intern_id);

    if(mysql_query(conn, query)) {
        fprintf(stderr, "\nError: Failed to update the record with id = %d in intern table table", intern_id);
        mysql_close(conn);
        exit(1);
    }
    printf("\nIntern performance details updated successfully");
}

void DisplayInternPerformance(MYSQL *conn, int intern_id) {
    char query[500];
    printf("5");
    sprintf(query, "select ID, NAME, TASK, STATUS, PERFORMANCE_SCORE from INTERN_DETAILS where ID='%d'", intern_id);

    if(mysql_query(conn, query)){
        fprintf(stderr,"%s\n",mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_use_result(conn);
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