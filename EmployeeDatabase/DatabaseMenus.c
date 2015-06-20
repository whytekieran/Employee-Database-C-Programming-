//including header file
#include "EmployeeDatabase.h"

int menu()
{
	int ans;
	do
	{
		printf("\n\n                                            Database Menu"); 
		printf("\n                                            ================="); 
		printf("\n                                            Enter a Number"); 
		printf("\n                                            1-Add employee"); 
		printf("\n                                            2-Display employee details"); 
		printf("\n                                            3-Update employee");  
		printf("\n                                            4-Delete employee"); 
		printf("\n                                            5-Display all employees by department"); 
		printf("\n                                            6-Employee Report"); 
		printf("\n                                            7-Save Employees and Exit"); 
		printf("\n                                            Enter Your Choice: "); 
		scanf("%d", &ans);
	}
	while(ans != 1 && ans != 2 && ans != 3 && ans != 4 && ans != 5 && ans != 6 && ans != 7);

	return ans;
}

//menu for updating employee attributes
int updateMenu()
{
	int ans;
	
	do
	{
		printf("\n\n                                            Database Update Menu"); 
		printf("\n                                           ======================"); 
		printf("\n                            What attribute of employee do you wish to update?"); 
		printf("\n\n                                             1-Employee Address"); 
		printf("\n                                             2-Employee Department"); 
		printf("\n                                             3-Employee Annual Salary");  
		printf("\n                                             Enter Your Choice: "); 
		scanf("%d", &ans);

		if((ans != 1) && (ans != 2) && (ans != 3))
		{
			printf("\n");
            printf("\n                                             Your input is incorrect.");
			printf("\n                                           Please enter number 1, 2 or 3");
			printf("\n");
		}
	}
	while(ans != 1 && ans != 2 && ans != 3);

	return ans;
}
