#ifndef __DATABASE_H_
#define __DATABASE_H__

//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//defining a boolean type
typedef int bool;
#define FALSE 0
#define TRUE 1

//constants
#define USERNAME_FILE "username.txt"
#define PASSWORD_FILE "password.txt"         //Files
#define EMPLOYEE_FILE "employees.txt"
#define REPORT_FILE "report.txt"
#define ENTER 13
#define TAB 9							     //Keys for password field
#define BACKSPACE 8
#define MAX_USERS 3
#define MAX_LENGTH 20

//functions
void loadUserData();                         //defined inside EmployeeDatabase.c
bool askForUserData();                       //defined inside EmployeeDatabase.c
int menu();                                  //defined inside DatabaseMenus.c
void addEmployee(struct node **, int);       //defined inside EmployeeDatabase.c
void displayDetails(struct node *);          //defined inside EmployeeDatabase.c
void deleteEmployee(struct node **);         //defined inside EmployeeDatabase.c
int updateMenu();                            //defined inside DatabaseMenus.c
void update(struct node **, int);            //defined inside EmployeeDatabase.c
int readEmployeeFile(struct node **);        //defined inside EmployeeDatabase.c
void displayByDepartment(struct node *);     //defined inside EmployeeDatabase.c
void departmentReport(struct node *);        //defined inside EmployeeDatabase.c
void saveEmployees(struct node *);	         //defined inside EmployeeDatabase.c

#endif