#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
#define bracket1Rate 0.10
#define bracket2Rate 0.15
#define bracket3Rate 0.20

typedef struct{
    char fName[20];
    char lName[20];
    char MI;
}name;

typedef struct{
    name empName;
    int idNum;
    int grossSalary;
    int rate;
    int hrsWorked;
    float takeHomeSalary;
}employeeInfo;

typedef struct node{
    employeeInfo employees;
    struct node *next;
}employeeRecord;

typedef struct{
    employeeRecord *employeeList;
    employeeRecord *bracket1; //Transfer all Employees who earn a grossSalary of 0-14,999, Tax rate = 10%, calculate takeHomeSalary here
    employeeRecord *bracket2; //Transfer all Employees who earn a grossSalary of 15,000-25,999, Tax rate = 15%, calculate takeHomeSalary here
    employeeRecord *bracket3; //Transfer all Employees who earn a grossSalary of 26,000 or higher, Tax rate = 20%, calculate takeHomeSalary here
}companyRecord;

employeeRecord *populate(int);
employeeInfo newEmployee(int,int,int,name);
name addName(char [],char[],char);
void taxBracketSeparation(companyRecord *);
void display(companyRecord );

int main(){
    companyRecord companyLists;
    int i=0;
    int employeeInitialCount=0;


    printf("Input how many employees: ");
    scanf("%d",&employeeInitialCount);

    companyLists.employeeList=populate(employeeInitialCount);

    taxBracketSeparation(&companyLists);

	display(companyLists);


}

void display(companyRecord companyList){
    if(companyList.bracket1 != NULL){
        printf("===Bracket 1===\n");
        while(companyList.bracket1 != NULL){
            printf("%d - %s,%s %c --- Php %.2f\n",companyList.bracket1->employees.idNum,companyList.bracket1->employees.empName.lName,
                  companyList.bracket1->employees.empName.fName, companyList.bracket1->employees.empName.MI, companyList.bracket1->employees.takeHomeSalary);
            companyList.bracket1 = companyList.bracket1->next;
        }
        printf("\n\n");
    }

    if(companyList.bracket2 != NULL){
        printf("===Bracket 2===\n");
        while(companyList.bracket2 != NULL){
            printf("%d - %s,%s %c --- Php %.2f\n",companyList.bracket2->employees.idNum,companyList.bracket2->employees.empName.lName,
                  companyList.bracket2->employees.empName.fName, companyList.bracket2->employees.empName.MI, companyList.bracket2->employees.takeHomeSalary);
            companyList.bracket2 = companyList.bracket2->next;
        }
        printf("\n\n");
    }
    if(companyList.bracket3 != NULL){
        printf("===Bracket 3===\n");
        while(companyList.bracket3 != NULL){
            printf("%d - %s,%s %c --- Php %.2f\n",companyList.bracket3->employees.idNum,companyList.bracket3->employees.empName.lName,
                  companyList.bracket3->employees.empName.fName, companyList.bracket3->employees.empName.MI, companyList.bracket3->employees.takeHomeSalary);
            companyList.bracket3 = companyList.bracket3->next;
        }
        printf("\n\n");
    }
}


void taxBracketSeparation(companyRecord *companyList){
    /* This function will separate all employees from the employeeList and add them into their appropriate Tax Bracket based on their Gross Pay. After which calculate their Take Home pay based on their tax bracket rate. The function will take in a companyRecord pointer and will not return anything. */
    companyList->bracket1 = NULL;
    companyList->bracket2 = NULL;
    companyList->bracket3 = NULL;
    employeeRecord **x = &companyList->bracket1;
    employeeRecord **y = &companyList->bracket2;
    employeeRecord **z = &companyList->bracket3;

    employeeRecord *trav = companyList->employeeList;

    while(trav != NULL){
        int salary = trav->employees.rate * trav->employees.hrsWorked;
        if(salary < 15000){
            *x = trav;
            trav = trav->next;
            (*x)->next = NULL;
            (*x)->employees.takeHomeSalary = salary - (salary * bracket1Rate);
            x = &(*x)->next;
        }else if(salary < 26000 && salary >= 15000){
            *y= trav;
            trav = trav->next;
            (*y)->next = NULL;
            (*y)->employees.takeHomeSalary = salary - (salary * bracket2Rate);
            y = &(*y)->next;
        }else if(salary >= 26000){
            *z = trav;
            trav = trav->next;
            (*z)->next = NULL;
            (*z)->employees.takeHomeSalary = salary - (salary * bracket3Rate);
            z = &(*z)->next;
        }
    }
}


employeeRecord *populate(int count){

    /* This function will take in a count of how many employees to add, and return an employeeRecord */
    employeeRecord *popu = NULL;

    int i=0;
    int idNum;
    int rate;
    int hrsWorked;
    char fName[20];
    char lName[20];
    char MI;

    for(i=0;i<count;i++){
    	printf("\n\n===EMPLOYEE %d===\n",i+1);

        //Write Code to Ask users for Input
        printf("Input First Name: ");
        scanf(" %s",fName);
        printf("Input Last Name: ");
        scanf(" %s",lName);
        printf("Input Middle Name: ");
        scanf(" %c",&MI);
        printf("Input Id Number: ");
        scanf("%d",&idNum);
        printf("Input Rate: ");
        scanf("%d",&rate);
        printf("Input Hours Worked: ");
        scanf("%d",&hrsWorked);

        employeeRecord *list = malloc(sizeof(employeeRecord));
    	list->employees=newEmployee(idNum,rate,hrsWorked,addName(fName,lName,MI));
    	list->next = popu;
        popu = list;

    	if(i==count-1){
    		printf("\n===============\n\n");
		}
	}

    return popu;

}
employeeInfo newEmployee(int idNum,int rate,int hrsWorked,name employeeName){
    employeeInfo newEmp;

    newEmp.empName=employeeName;
    newEmp.idNum=idNum;
    newEmp.rate=rate;
    newEmp.hrsWorked=hrsWorked;

    //Write Code to Calculate grossSalary;




    return newEmp;

}
name addName(char fName[],char lName[],char MI){

    /* This function takes in 2 Strings and a Character, it will then populate a new name structure variable based on the parameters passed towards this function and aim to return it back to the calling function */

    name employeeName;

    strcpy(employeeName.fName,fName);
    strcpy(employeeName.lName,lName);
    employeeName.MI=MI;

    return employeeName;

}
