//including header file
#include "EmployeeDatabase.h"

//All global variables
//Login structure to hold usernames and passwords from text files
struct login
{
   char username[MAX_LENGTH];   
   char password[MAX_LENGTH];  
};

//structure for date
struct Date
{
	int day;
	int month;
    int year;
};

//structure for employee
struct Employee
{
	int employeeId;
	char employeeFirstName[15];
	char employeeLastName[15];
	char employeeAddress[20];
	char department[10];
	struct Date joinDate;
	float annualSalary;
	char emailAddress[20];
};

//structure for a node
struct node
{
	struct Employee employee; 
    struct node *nextNodesAddr; 
};

//create an array of login structures
struct login users[MAX_USERS];

//main function
void main()
{
	bool validData = 0;
	int choice;
	int updateChoice;
	int id;
	struct node *head;
	head = (struct node*)malloc(sizeof(struct node)); //Allocating memory and creating a node. head now points to the node.
	head->nextNodesAddr = NULL; //heads hext address is null head node in the list
	
	id = readEmployeeFile(&head); //Reads employees from file into linked list returns current id as its incremented

	loadUserData();//Load in usernames/passwords from text files
	//add function to read file and add employees to linked list
	
	do
	{
	   validData = askForUserData(); //ask and keep asking for username/password until a correct one is entered
	}
	while(validData == 0);

	do
	{
       choice = menu();//Calls the menu for employee database options, returns the choice.

	   //switches the choice and performs a function//main menu.
	   switch(choice)
	   {
		  case 1:
			++id;							//selection 1, increment id and call addEmployee function
			addEmployee(&head, id);
			break;
		  case 2:
            displayDetails(head);			//selection 2, call displayDetails
			break;
		  case 3:
			updateChoice = updateMenu();
			update(&head, updateChoice);	//selection 3, call updatemenu and return choice then pass it to update
			break;
		  case 4:
			deleteEmployee(&head);			//selection 4, call deleteEmployee
			break;
		  case 5:
			displayByDepartment(head);      //selection 5, call displayByDepartment which displays all employees in a department
			break;
		  case 6:
			departmentReport(head);			//selection 6, call departmentReport which creates a report and writes to file
			break;
		  case 7:
			saveEmployees(head);			//save all employees back out to the employees.txt file
			printf("\n  Employees saved to employee.txt");   
			printf("\n  GoodBye, Have a nice day :D");             //selection 7, close the program
			break;
	   }
	}
	while(choice != 7);
	
	printf("\n\n\n");
	system("pause");
}//end main

void loadUserData()//loading in data from text files for username/password
{
   FILE * fru;                       //declare pointers for read to files
   FILE * frp; 
   fru = fopen(USERNAME_FILE, "r");  //open files
   frp = fopen(PASSWORD_FILE, "r");
  
   if (fru == NULL || frp == NULL)   //check if the files exist
   {
      printf("\t\tFile could not be opened");
   }
   else
   {
	  //Read in the data from file into the members of my array of login structures
	  int i = 0;
	   
      while(fscanf(fru,"%s",users[i].username) != EOF)//loop through username.txt
	  {
		  ++i;
	  }

	  i = 0;

	  while(fscanf(frp,"%s",users[i].password) != EOF)//loop through password.txt
	  {
		  ++i;
	  }
	   
	  fclose(fru);//close the files
	  fclose(frp);
   }
}

//function that asks for username/password
bool askForUserData()
{
    char password[MAX_LENGTH];
	int i = 0;
	char ch;
	char username[MAX_LENGTH];

	printf("\n\n                                              Employee Database");
	printf("\n                                           =======================");

	printf("\n\n                            6 Character Username and Password - Case Sensitive");

    printf("\n\n                                              Enter Username: ");
	fflush(stdin);
	scanf("%s", username);
											  
    printf("\n                                              Enter Password: ");

	//Changes each letter of password to an * and also takes backspace into account
	while(1)
	{
	    ch = getch();

		if(ch == ENTER || ch == TAB)//when user hit enter or tab a number corresponds to those keys
		{
			password[i] = '\0'; //add the null character
			break;
		}
		else if(ch == BACKSPACE)//if user hits backspace
		{
			if (i > 0)
			{
				--i;              //de-increment
				printf("\b \b"); //and print the backspace
			}
		}
		else
		{
			password[i++] = ch;
			printf("* \b");
		}
	}

	//Compares the username/password entered with the ones read in from the files.
	for(i = 0; i < MAX_USERS; ++i)
	{
		if(strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
		{
			printf("\n\n                                      Correct Username and Password");
			return 1;
		}
	}
	
	printf("\n\n                                       Incorrect Username and Password");
	return 0;
}

//function to add a new employee (struct) to linked list
void addEmployee(struct node **head, int id)
{
	int i;
	int j = 0;
	bool valid = 0;
	int validCnt = 0;
	bool foundSymbol = 0;
	char emailValid[4];
	char emailValidCheck[] = "moc.";
	struct node *newNode;  
    newNode = (struct node*)malloc(sizeof(struct node)); //create and allocate memory for new node 

	newNode->employee.employeeId = id;
	printf("\nEmployees Id: %d ", newNode->employee.employeeId); 
	
	printf("\nEnter Employee First Name: "); 
	scanf("%s", &newNode->employee.employeeFirstName);    
	fflush(stdin);

	printf("\nEnter Employee Last Name: "); 
	scanf("%s", &newNode->employee.employeeLastName);    
	fflush(stdin);                                                   //ask the user to start entering data

	printf("\nEnter Employee Address: "); 
	scanf("%s", &newNode->employee.employeeAddress);  
	fflush(stdin);

	printf("\nEnter Employee Department: "); 
	scanf("%s", &newNode->employee.department); 
	fflush(stdin);

	//beginning validation for date joined
	do
	{
		
		printf("\nEnter Employee Month Joined: "); 
	    scanf("%d", &newNode->employee.joinDate.month); 
		fflush(stdin);

        if(newNode->employee.joinDate.month < 1 || newNode->employee.joinDate.month > 12)      //validate the month between 1-12
		{
			printf("Month Needs to be between 1-12");
		}
	}
	while(newNode->employee.joinDate.month < 1 || newNode->employee.joinDate.month > 12);

	if(newNode->employee.joinDate.month == 9 || newNode->employee.joinDate.month == 4 || newNode->employee.joinDate.month == 6 
			   || newNode->employee.joinDate.month == 11) //if month is 9, 4, 6 or 11
	{
		do
		{
			printf("\nEnter Employee Day Joined: "); 
			scanf("%d", &newNode->employee.joinDate.day); //ask for join date
			fflush(stdin);

			if(newNode->employee.joinDate.day < 1 || newNode->employee.joinDate.day > 30) //must be between 1-30
			{
				printf("\nDay between 1-30 is needed"); 
			}
		}
		while(newNode->employee.joinDate.day < 1 || newNode->employee.joinDate.day > 30);
	}
	else if(newNode->employee.joinDate.month == 1 || newNode->employee.joinDate.month == 3 || newNode->employee.joinDate.month == 5 
		   || newNode->employee.joinDate.month == 7 || newNode->employee.joinDate.month == 8 || newNode->employee.joinDate.month == 10
		   || newNode->employee.joinDate.month == 12)//else if moth is 1,3,5,7,8,,10 or 12
	{
		do
		{
			printf("\nEnter Employee Day Joined: "); //ask for join date
			scanf("%d", &newNode->employee.joinDate.day);
			fflush(stdin);

			if(newNode->employee.joinDate.day < 1 || newNode->employee.joinDate.day > 31)//must be between 1-31
			{
				printf("\nDay between 1-31 is needed"); 
			}
		}
		while(newNode->employee.joinDate.day < 1 || newNode->employee.joinDate.day > 31);
	}
	else//else the moth must be 2 (feb)
	{
		do
		{
			printf("\nEnter Employee Day Joined: "); 
			scanf("%d", &newNode->employee.joinDate.day); //ask for join days
			fflush(stdin);

			if(newNode->employee.joinDate.day < 1 || newNode->employee.joinDate.day > 29)//must be between 1-29
			{
				printf("\nYou choose febuary, day must be between 1-29"); 
			}
		}
		while(newNode->employee.joinDate.day < 1 || newNode->employee.joinDate.day > 29);
	}
	
	do
	{
		printf("\nEnter Employee Year Joined: ");  //year must be between 1965-2015 more realistic
	    scanf("%d", &newNode->employee.joinDate.year); 
		fflush(stdin);

		if(newNode->employee.joinDate.year < 1965 || newNode->employee.joinDate.year > 2015)
		{
			printf("\nYear no less than 1965 and no more than 2015"); 
		}
	}
	while(newNode->employee.joinDate.year < 1965 || newNode->employee.joinDate.year > 2015);

	//end of validation for date joined

	printf("\nEnter Employee Annual Salary: "); 
	scanf("%f", &newNode->employee.annualSalary); 
	fflush(stdin);
	
	//Email validation inside do/while loop
	do
	{
		printf("\nEnter Employee Email: "); 
		scanf("%s", &newNode->employee.emailAddress);  //ask user for email
		fflush(stdin);

		for(i = 0; i < 20; ++i) //firstly loop through the address
		{
			if(newNode->employee.emailAddress[i] == '@') //if we find the @ symbol
			{
				foundSymbol = 1; //foundSymbol is true
				break;
			}
		}

	    for(i = 19; i >= 0; --i) // next start at the end of the array loop backwards
		{
			if(newNode->employee.emailAddress[i] == '\0') //loop back until we find the null character and when we find it
			{
				while(j != 4) //loop 4 times (Four letters in ".com")
				{
					--i;
					emailValid[j] = newNode->employee.emailAddress[i]; //fill emailValid array, if its valid, the array will contain moc.
					++j;
				}
			}
		}

		for(i = 0; i < 4; ++i)//then loop four times
		{
			if(emailValid[i] == emailValidCheck[i])//compare emailValid with a pre-initialized array containing moc.
			{
				++validCnt; //count each valid match
				
				if(validCnt == 4 && foundSymbol == 1) //if all four match and the found @ symbol is also true
				{
					printf("\nValid Email Address"); //valid email
					valid = 1; //valid is true
				}
			}
			else
			{
				printf("\nInvalid Email Address - Please try again");
				printf("\nEmail must contain @ and end with .com");      //otherwise its invalid
			    validCnt = 0;
			    j = 0;                   //set all counters and booleans back to orginal values
			    foundSymbol = 0;
				break;                      //break the loop and start again.
			}
		}
	}
	while(valid == 0);

	newNode->nextNodesAddr = *head; 
	*head = newNode;                     //Adds each new employee to the start of the list
}

//displays details of a specific employee, depeding on id entered
void displayDetails(struct node *head)
{
	int searchNumber;
	struct node *temp;  
	temp = head; //assign temp the address of head                                     
    
	printf("\nEnter the Id number of the employee your looking for: ");//ask user for id number
	scanf("%d", &searchNumber);

    while(temp->nextNodesAddr != NULL) //Loop through the list
	{  
		if(temp->employee.employeeId == searchNumber)//if we find the id number, display the employee
		{
			printf("\nEmployee id: %d", temp->employee.employeeId);
			printf("\nEmployee First Name: %s", temp->employee.employeeFirstName);
			printf("\nEmployee Last Name: %s", temp->employee.employeeLastName);
			printf("\nEmployee Address: %s", temp->employee.employeeAddress);
			printf("\nEmployee Department: %s", temp->employee.department);
			printf("\nEmployee Day Joined: %d", temp->employee.joinDate.day);        //print out the employee details
			printf("\nEmployee Month Joined: %d", temp->employee.joinDate.month);
			printf("\nEmployee Year Joined: %d", temp->employee.joinDate.year);
			printf("\nEmployee Annual Salary: %7.2f", temp->employee.annualSalary);
			printf("\nEmployee Email: %s", temp->employee.emailAddress);
			return;     //return function call
		}

		temp = temp->nextNodesAddr;  //increment the address  
	}

	printf("No Record Found");
}

//function to delete an employee from the list
void deleteEmployee(struct node **head)
{
	int id;
	int icnt = 0;
	char name[50];
	char choice;           //function variables
	struct node *temp;
	struct node *prev;
	temp = *head;
	
	do
	{
	   printf("\n\nDelete Employee by Id or First Name: (I/Id or N/Name) ");//ask user which way they want to search id or name?
	   fflush(stdin);
       choice = getchar();

	   if(choice != 'i' && choice != 'I' && choice != 'n' && choice != 'N')
	   {
		   printf("\nWrong choice please select again.");                       //validation
	   }
	}
	while(choice != 'i' && choice != 'I' && choice != 'n' && choice != 'N');//keep looping while data is invalid

	if(choice == 'i' || choice == 'I')//if id
	{
		printf("\nEnter id number of employee you wish to delete: ");//ask user for id of employee they are looking for
		scanf("%d", &id);

		while(temp->nextNodesAddr != NULL) //loop through list  
	    {         
		    if(temp->employee.employeeId == id)//if id matches the searched id
			{
				if(icnt == 0) //and if icnt is 0 (if the node for deletion is the first node in the list)
				{
					*head = temp->nextNodesAddr; //the second node in the list is now the first node
					free(temp);                  //free memory of the first
					printf("Deleted");
					return;
				}
				else
				{
					prev->nextNodesAddr = temp->nextNodesAddr; //the node prev of the one for deletion now points to the one after the
					free(temp);									//one for deletion, then free memory of the node to be deleted
					printf("Deleted");
					return;
				}
			}
		   
			prev = temp;                           //make sure prev is always equal to node before its incremented
			temp = temp->nextNodesAddr; 
			++icnt;
		}

		printf("No Record found");
    }
	else
	{
		printf("\nEnter first name of employee you wish to delete: ");//same formula but this time searching by name
		scanf("%s", name);

		while(temp->nextNodesAddr != NULL)   
	    {         
		    if(stricmp(name, temp->employee.employeeFirstName) == 0)//comparing for deletion of employee by name
			{
				if(icnt == 0)
				{
					*head = temp->nextNodesAddr;
					free(temp);
					printf("Deleted");
					return;
				}
				else
				{
					prev->nextNodesAddr = temp->nextNodesAddr;
					free(temp);
					printf("Deleted");
					return;
				}
			}
		   
			prev = temp;
			temp = temp->nextNodesAddr; 
			++icnt;
		}

		printf("No Record found");
	}
}
//function to update employee attributes
void update(struct node **head, int num)//num is passed in from variable containing value returned from menu() function
{
	char choice;
	int id;
	char name[50];
	struct node *temp;
	temp = *head;

	if(num == 1)//if num is 1 choosen to alter address attribute
	{
		do
		{
			printf("\n\nUpdate address of Employee by Id or First Name: (I/Id or N/Name) ");//ask user to search by id or name
			fflush(stdin);
			choice = getchar();

			if(choice != 'i' && choice != 'I' && choice != 'n' && choice != 'N')
			{
			   printf("\nWrong choice please select again.");
		    }
	   }
	   while(choice != 'i' && choice != 'I' && choice != 'n' && choice != 'N');

	   if(choice == 'i' || choice == 'I')//if by id
	   {
		   printf("\nEnter id number of employee who's address you wish to update: ");//ask for the id number
		   scanf("%d", &id);

		   while(temp->nextNodesAddr != NULL)   //loop through the list
	       { 
			   if(temp->employee.employeeId == id)//if we find the id number
			   {
				   printf("\nEnter Employee Address: "); //ask for the new address
	               fflush(stdin);
	               scanf("%s", temp->employee.employeeAddress); 
				   return;
			   }

			   temp = temp->nextNodesAddr; //incrementing through the loop
		   }

		   printf("No Record Found");
	   }
	   else //same except we search by name
	   {
		   printf("\nEnter first name of employee who's address you wish to update: ");
		   scanf("%s", name);

		   while(temp->nextNodesAddr != NULL)   
	       {         
		      if(stricmp(name, temp->employee.employeeFirstName) == 0)//searching for match in name
			  {
				 printf("\nEnter Employee Address: "); 
	             fflush(stdin);
	             scanf("%s", temp->employee.employeeAddress); 
		         return;
			  }

			  temp = temp->nextNodesAddr; 
		   }

		printf("No Record Found");
	   }
    }
	else if(num == 2)//update department for choice 2 exact same as choice 1
	{
		do
		{
			printf("\n\nUpdate department of Employee by Id or First Name: (I/Id or N/Name) ");
			fflush(stdin);
			choice = getchar();

			if(choice != 'i' && choice != 'I' && choice != 'n' && choice != 'N')
			{
			   printf("\nWrong choice please select again.");
		    }
	   }
	   while(choice != 'i' && choice != 'I' && choice != 'n' && choice != 'N');

	   if(choice == 'i' || choice == 'I')
	   {
		   printf("\nEnter id number of employee who's department you wish to update: ");
		   scanf("%d", &id);

		   while(temp->nextNodesAddr != NULL)   
	       { 
			   if(temp->employee.employeeId == id)
			   {
				   printf("\nEnter Employee Department: "); 
	               fflush(stdin);
	               scanf("%s", temp->employee.department); 
				   return;
			   }

			   temp = temp->nextNodesAddr; 
		   }

		   printf("No Record Found");
	   }
	   else
	   {
		   printf("\nEnter first name of employee who's department you wish to update: ");
		   scanf("%s", name);

		   while(temp->nextNodesAddr != NULL)   
	       {         
		      if(stricmp(name, temp->employee.employeeFirstName) == 0)
			  {
				 printf("\nEnter Employee Department: "); 
	             fflush(stdin);
	             scanf("%s", temp->employee.department); 
		         return;
			  }

			  temp = temp->nextNodesAddr; 
		   }

		printf("No Record Found");
	   }
	}
	else if(num == 3)//update annual for choice 2 exact same as choice 1 just different attribute change
	{
	    do
		{
			printf("\n\nUpdate Annual Salary of Employee by Id or First Name: (I/Id or N/Name) ");
			fflush(stdin);
			choice = getchar();

			if(choice != 'i' && choice != 'I' && choice != 'n' && choice != 'N')
			{
			   printf("\nWrong choice please select again.");
		    }
	   }
	   while(choice != 'i' && choice != 'I' && choice != 'n' && choice != 'N');

	   if(choice == 'i' || choice == 'I')
	   {
		   printf("\nEnter id number of employee who's annual salary you wish to update: ");
		   scanf("%d", &id);

		   while(temp->nextNodesAddr != NULL)   
	       { 
			   if(temp->employee.employeeId == id)
			   {
				   printf("\nEnter Employee Annual Salary: "); 
	               fflush(stdin);
	               scanf("%f", &temp->employee.annualSalary); 
				   return;
			   }

			   temp = temp->nextNodesAddr; 
		   }

		   printf("No Record Found");
	   }
	   else
	   {
		   printf("\nEnter name of employee who's annual salary you wish to update: ");
		   scanf("%s", name);

		   while(temp->nextNodesAddr != NULL)   
	       {         
		      if(stricmp(name, temp->employee.employeeFirstName) == 0)
			  {
				 printf("\nEnter Employee Annual Salary: "); 
	             fflush(stdin);
	             scanf("%f", &temp->employee.annualSalary); 
		         return;
			  }

			  temp = temp->nextNodesAddr; 
		   }

		printf("No Record Found");
	  }
   }
}

int readEmployeeFile(struct node **head)
{
	int icnt = 0;
	struct Employee employee;
    struct node *newNode;
    FILE * fptr;                       
    fptr = fopen(EMPLOYEE_FILE, "r");                       //open employee.txt file for reading
    newNode = (struct node*)malloc(sizeof(struct node)); //create and allocate memory for new node 
	  
    if(fptr == NULL)
    {
 	   printf("File Not Found"); //check for the file
	}
	else
    {
	   while(fscanf(fptr,"%d %d %d %d %f %15s %15s %20s %10s %20s", &newNode->employee.employeeId, &newNode->employee.joinDate.day, &newNode->employee.joinDate.month,
			 &newNode->employee.joinDate.year, &newNode->employee.annualSalary, newNode->employee.employeeFirstName, newNode->employee.employeeLastName, newNode->employee.employeeAddress, 
			 newNode->employee.department, newNode->employee.emailAddress) != EOF) //while this data is being read and its not the EOF
		     {
				++icnt; //increment counter

			    newNode->nextNodesAddr = *head;   //add the data to the new Node
	            *head = newNode;                 //add the node to the start of the list

			    newNode = (struct node*)malloc(sizeof(struct node)); //create memory for the next node
	         }

	   fclose(fptr); //close the file pointer
	   return icnt; //return the count number which will be used as id when user enters next employee
	}
}

void displayByDepartment(struct node *head)//print employees by department
{
	int recordCnt = 0;
	char department[10];
	struct node *temp;
	temp = head;

	printf("Enter Employees Department: ");   //ask for department
	scanf("%s", department);  

	while(temp->nextNodesAddr != NULL)//loop through the linked list
	{
		if(stricmp(department, temp->employee.department) == 0)//if theres a match
		{
			++recordCnt; //increment counter

			printf("\nEmployee id: %d", temp->employee.employeeId);
			printf("\nEmployee First Name: %s", temp->employee.employeeFirstName);
			printf("\nEmployee Last Name: %s", temp->employee.employeeLastName);
			printf("\nEmployee Address: %s", temp->employee.employeeAddress);
			printf("\nEmployee Department: %s", temp->employee.department);               //print employee details
			printf("\nEmployee Day Joined: %d", temp->employee.joinDate.day);
			printf("\nEmployee Month Joined: %d", temp->employee.joinDate.month);
			printf("\nEmployee Year Joined: %d", temp->employee.joinDate.year);
			printf("\nEmployee Annual Salary: %7.2f", temp->employee.annualSalary);
			printf("\nEmployee Email: %s", temp->employee.emailAddress);
			printf("\n================================================");
			printf("\n");
		}

		temp = temp->nextNodesAddr; //increment address
	}

	printf("%d Records Found", recordCnt); //print how many employee records where found
}

void departmentReport(struct node *head) //creates a record for selected department and writes to file
{
	char department[10];
	float totalSalary = 0;
	float totalBonus = 0;
	int employeeCnt = 0;
	struct node *temp;
	FILE * fptr;
	fptr = fopen(REPORT_FILE, "w"); //open report.txt file for writing
	temp = head;

	printf("Enter Department for Report: "); //ask for department you wish the report to be about
	scanf("%s", department);

	while(temp->nextNodesAddr != NULL) //loop through the linked list
	{
		if(stricmp(department, temp->employee.department) == 0)//for each employee found in this department
		{
			++employeeCnt;                              //increment employee count
			totalSalary += temp->employee.annualSalary; //add employees salary to total salary

			if((2015 - temp->employee.joinDate.year) > 10)              //check how long they have been an employee then
			{                                                          // add a percent bonus to total bonus based on that number
				totalBonus += (temp->employee.annualSalary * .05);
			}
			else if((2015 - temp->employee.joinDate.year) >= 5 && (2015 - temp->employee.joinDate.year) <= 10)
			{
				totalBonus += (temp->employee.annualSalary * .04);
			}
			else if((2015 - temp->employee.joinDate.year) < 5)
			{
				totalBonus += (temp->employee.annualSalary * .03);
			}
		}
		
		temp = temp->nextNodesAddr; 
	}

	if(employeeCnt > 0) //if we found at least one employee
	{
		fprintf(fptr, "Department Report");
		fprintf(fptr,"\nDepartment Name: %s", department);
		fprintf(fptr,"\nNumber of Employees: %d", employeeCnt);
		fprintf(fptr,"\nTotal Annual Salary: %8.2f", totalSalary);  //print to file
		fprintf(fptr,"\nTotal Bonuses: %6.2f", totalBonus);

		printf("\nDepartment Report");
		printf("\nDepartment Name: %s", department);
		printf("\nNumber of Employees: %d", employeeCnt);        //print to screen
		printf("\nTotal Annual Salary: %8.2f", totalSalary);
		printf("\nTotal Bonuses: %6.2f", totalBonus);

		printf("\nDepartment Records have been printed to the record.txt file", totalBonus);
	}
	else
	{
		printf("\nNo employee Records Found for this department");  //otherwise simply output no records found message
	}

	fclose(fptr);
}

//save employees function, writes all the employees to a file before the programme exits
void saveEmployees(struct node *head)
{
	FILE * fptr;   
	struct node *temp;
	temp = head;                         //variables
	fptr = fopen(EMPLOYEE_FILE, "w"); 

	if(fptr == NULL) //if file pointer is null
	{
		printf("File was not found");
	}
	else
	{
		while(temp->nextNodesAddr != NULL) //loop through the linked list
		{
			fprintf(fptr,"\n %d %d %d %d %f %15s %15s %20s %10s %20s", temp->employee.employeeId, temp->employee.joinDate.day, temp->employee.joinDate.month,
				   temp->employee.joinDate.year, temp->employee.annualSalary, temp->employee.employeeFirstName, temp->employee.employeeLastName,
				   temp->employee.employeeAddress, temp->employee.department, temp->employee.emailAddress);  //print all employees out to file
		
			temp = temp->nextNodesAddr; //increment through the list
		}
	}
}
