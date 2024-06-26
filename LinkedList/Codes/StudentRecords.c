#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef struct {
    char fName[50];
    char lName[50];
    char middleInitial;
} name;

typedef struct {
    name studentName;
    int idNum;
    int studentGrades[3];
} studentDetail;

typedef struct node {
    studentDetail student;
    struct node *next;
} classRecord;

typedef struct {
    classRecord *classList;
    classRecord *examRetake[3];
} classResults;

studentDetail addStudent(char *fName, char *lName, char mi, int idNum, int grades[]);
void populate(classRecord **record, int classCount);
void checkExams(classResults *results);
void display(classRecord *node, int i, int classCount);

int main() {
    int classCount;
    classResults results;
    results.classList = NULL;

    printf("Input Number of Students in Class:");
    scanf("%d", &classCount);

    /*CODE TO FIRST CHECK IF CLASS SIZE IS CORRECT*/
    if (classCount > MAX) {
        printf("Maximum Number of Students per Class is only %d", MAX);
        return 0;
    }
    /*FUNCTION CALL TO POPULATE THE ARRAY*/
    populate(&results.classList, classCount);

    /*FUNCTION CALL TO CHECK WHO NEEDS TO RETAKE WHICH EXAMS*/
    checkExams(&results);

    /*DISPLAY*/
    for (int i = 0; i < 3; i++) {
        printf("Retakers Needed for Exam %d:", i+1);
        if(results.examRetake[i] == NULL){
            printf("No Retakers for Exam %d\n\n",i+1);
        }else{
            display(results.examRetake[i], i, classCount);
        }
    }

    return 0;
}

void display(classRecord *node, int i, int classCount) {
    classRecord *check = node;
    int j = 0;
    
    while(check != NULL){
        j++;
        check = check->next;
    }
    if(j == classCount){
        printf("All Students Have to Retake Exam %d",i+1);
    }else{
        while (node != NULL) {
            printf("%s ", node->student.studentName.fName);
            node = node->next;
        }   
    }
    printf("\n\n");
}

void checkExams(classResults *results) { //pointer as we input data to examRetake

    for (int i = 0; i < 3; i++) {
        results->examRetake[i] = NULL;
    }

    classRecord *current = results->classList;
    while (current != NULL) {
        for (int i = 0; i < 3; i++) {
            if (current->student.studentGrades[i] < 60) {
                classRecord *retake = malloc(sizeof(classRecord)); //Generates Linklist and pass to a specifc examretake index
                retake->student = current->student;
                retake->next = results->examRetake[i]; // Add front
                results->examRetake[i] = retake;
            }
        }
        current = current->next;
    }
}

void populate(classRecord **record, int classCount) {
    for (int i = 0; i < classCount; i++) {
        printf("===STUDENT %d===\n\n", i + 1);
        char fName[50];
        char lName[50];
        char MI;
        int idNum;
        int grades[3];

        printf("Input First Name: ");
        scanf("%s", fName);
        printf("Input Last Name: ");
        scanf("%s", lName);
        printf("Input Middle Initial: ");
        scanf(" %c", &MI);
        printf("Input ID Number: ");
        scanf("%d", &idNum);

        for (int j = 0; j < 3; j++) {
            printf("Input Exam Score %d: ", j + 1);
            scanf("%d", &grades[j]);
        }

        classRecord *temp = malloc(sizeof(classRecord));
        temp->student = addStudent(fName, lName, MI, idNum, grades);
        temp->next = *record;
        *record = temp;          //Add front
    }
}

studentDetail addStudent(char *fName, char *lName, char mi, int idNum, int grades[]) {
    studentDetail details;

    details.studentName.middleInitial = mi;
    strcpy(details.studentName.fName, fName);
    strcpy(details.studentName.lName, lName);

    details.idNum = idNum;

    for (int i = 0; i < 3; i++) {
        details.studentGrades[i] = grades[i];
    }

    return details;
}