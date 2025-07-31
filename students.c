#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "studentMarkSheet.h"

ClassRecord classRecord = {.students=NULL,.noOfStudents = 0, .noOfStuPassed = 0, .avgOfStudentsPassed = 0};

void displayMenu();

int main() {
    FILE *studentsFile;
    StudentMarkSheet temp;
    int i = 0;

    studentsFile = fopen("studentsRecord.txt", "r+"); 
    if (studentsFile == NULL) {
        printf("File Not Opened\n");
        return 1;
    }

    classRecord.noOfStudents=0;
    rewind(studentsFile);
    while ((fscanf(studentsFile, "%s %s %d %f %f %f %f %f %c",
                  temp.firstName, temp.lastName, &temp.rollNo,
                  &temp.marks[0], &temp.marks[1], &temp.marks[2],
                  &temp.totalMarks, &temp.avg,&temp.isPass)) == 9) {
        classRecord.noOfStudents++;
        classRecord.students = realloc(classRecord.students, classRecord.noOfStudents * sizeof(StudentMarkSheet));
        if (classRecord.students == NULL) {
            printf("Memory Reallocation Failed\n");
            fclose(studentsFile);
            return 1;
        }
        classRecord.students[i] = temp;
        i++;
    }
    char ch;
    while(ch != 'q')
    {
        displayMenu();
        scanf(" %c",&ch);
        switch(ch){
            case '1': printAllStudentsRecord(classRecord);break;
            case '2': addStudent(&classRecord,studentsFile);break;
            case '3': exportStudentReport(classRecord);break;
            case '4': findStudent(classRecord);break;
        }
    }
    ch = 'p';
    fclose(studentsFile);
    return 0;
}
void displayMenu(){
    system("clear");
    printf("\n\n     ------>   Student Report   <------     \n\n");
    printf("                                 Press q to exit\n\n");
    printf("   1. View All Student Reports\n\n");
    printf("   2. Add Student \n\n");
    printf("   3. Export Student Report\n\n");
    printf("   4. Search Student by Roll no\n\n");
    printf("           Enter your choice  : ");
}
