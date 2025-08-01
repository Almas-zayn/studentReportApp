#include "studentMarkSheet.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int addStudent(ClassRecord *classRecord,FILE *studentFile)
{  
      (classRecord->noOfStudents)++;
      StudentMarkSheet temp={.totalMarks=0.0,.avg=0.0};
      printf("Enter the First Name : ");

//------first and Last Name      

  FIRSTNAME: scanf("%s",temp.firstName); 
      if(stringValidate(temp.firstName)){
          printf("Enter the First name correctly : ");
          goto FIRSTNAME;
      }

      printf("Enter the Last Name : ");
  LASTNAME: scanf("%s",temp.lastName);
      if(stringValidate(temp.lastName)){
          printf("Enter the Last name correctly : ");
          goto LASTNAME;
      }

//-------Roll number

      printf("Enter the RollNumber : ");
  ROLLNO: scanf("%d",&temp.rollNo);
      if(numberValidate(temp.rollNo)){
         printf("Enter the roll no correctly (0 - 999): ");
         goto ROLLNO;
      }

//--------Marks

      printf("Enter the Marks of Subject 1 :");
  MARK1: scanf("%f",&temp.marks[0]);
      if(validateMarks(temp.marks[0])){
         printf("Enter the marks correctly - (0-100) : ");
         goto MARK1;
      }

      printf("Enter the Marks of Subject 2 :");
  MARK2: scanf("%f",&temp.marks[1]);
      if(validateMarks(temp.marks[1])){
         printf("Enter the marks correctly - (0-100) : ");
         goto MARK2;
      }

      printf("Enter the Marks of Subject 3 :");
  MARK3: scanf("%f",&temp.marks[2]);
      if(validateMarks(temp.marks[2])){
         printf("Enter the marks correctly - (0-100) : ");
         goto MARK3;
      }

//---------Pass or Fail

   if(temp.marks[0] < 35 || temp.marks[1] < 35 || temp.marks[2] < 35){
      temp.isPass='F';
   } else{
      temp.isPass = 'P';
   }

//---------Average

   for(int i=0;i<3;i++)
      temp.totalMarks += temp.marks[i];
   temp.avg = temp.totalMarks / 3;

//--------- Writing Data to File   

   classRecord->students = (StudentMarkSheet *)realloc(classRecord->students,(classRecord->noOfStudents)*sizeof(StudentMarkSheet));
   if(classRecord->students == NULL){
      printf("Memory Not allocated");
      return -1;
   }else{
      classRecord->students[classRecord->noOfStudents -1] = temp;
      printf("\n\nAdding student to file\n\n");
      fseek(studentFile,0,SEEK_END);
      if((fprintf(studentFile, "\n%s %s %d %f %f %f %f %f %c",
                  temp.firstName, temp.lastName, temp.rollNo,
                  temp.marks[0], temp.marks[1], temp.marks[2],
                  temp.totalMarks, temp.avg,temp.isPass)))
      {
        printf("Student Data added to Student Record");
      }
   }
   return 0;  
}

void exportStudentReport(ClassRecord classRecord) {
    int rollno;
    printf("Enter Roll Number to export report: ");
    scanf("%d", &rollno);

    int found = 0;
    for (int i = 0; i < classRecord.noOfStudents; i++) {
        if (rollno == classRecord.students[i].rollNo) {
            found = 1;

            char fileName[100];
            sprintf(fileName, "%s%d.txt", classRecord.students[i].firstName, classRecord.students[i].rollNo);
            FILE* exportReportFile = fopen(fileName, "w");

            if (!exportReportFile) {
                printf("Failed to create report file.\n");
                return;
            }

            StudentMarkSheet student = classRecord.students[i];

            fprintf(exportReportFile, "\n  First Name  : %s\n", student.firstName);
            fprintf(exportReportFile, "  Last  Name  : %s\n", student.lastName);
            fprintf(exportReportFile, "  Roll Number : %d\n\n\n", student.rollNo);
            fprintf(exportReportFile, "-------------------------------------------------\n");
            fprintf(exportReportFile, "| S.no  |  Subject         |     Marks          |\n");
            fprintf(exportReportFile, "-------------------------------------------------\n");
            for (int j = 0; j < 3; j++) {
                fprintf(exportReportFile, "|  %d    |   Subject %-6d |       %6.2f       |\n", j+1, j+1, student.marks[j]);
            }
            fprintf(exportReportFile, "-------------------------------------------------\n");
            fprintf(exportReportFile, "|            Total Marks     :  %6.2f          |\n", student.totalMarks);
            fprintf(exportReportFile, "-------------------------------------------------\n");
            fprintf(exportReportFile, "                        Average  :   %6.2f \n", student.avg);
            fprintf(exportReportFile, "                        Result   :   %s \n", student.isPass == 'P' ? "PASS" : "FAIL");

            fclose(exportReportFile);
            printf("Report successfully exported to file: %s\n", fileName);
            return;
        }
    }

    if (!found) {
        printf("Student with roll number %d not found.\n", rollno);
    }
}
void viewClassReport(ClassRecord *classRecord){
    system("clear");
     unsigned int noOfpassed=0;
     int noofStu = classRecord ->noOfStudents;
     for(int i = 0 ;i < noofStu ; i++){
        if(classRecord->students[i].isPass == 'P'){
            noOfpassed++;
        }
     }
     classRecord->noOfStuPassed = noOfpassed;
     classRecord->avgOfStudentsPassed = ((float )classRecord->noOfStuPassed / ((float )classRecord->noOfStudents) ) * 100;
     printf("\n\n -------->  CLASS REPORT  <-------\n\n\n");
     printf("     Class Name            : %s\n\n",classRecord->className);
     printf("     Total Students        : %d\n\n",classRecord->noOfStudents);
     printf("     No.of Students Passed : %d\n",classRecord->noOfStuPassed);
     printf("     No.of Students Failed : %d\n\n",(classRecord->noOfStudents - classRecord->noOfStuPassed));
     printf("     Pass Percentage       : %0.2f\n",(classRecord->avgOfStudentsPassed));
    // printf("Topper of Class : ");

 //   Students Data
   printf("\n\n--------------------------------------------------------------------------------------------------------\n");
   printf("| S.no |  Student Name    | RollNo  |  Sub 1 | sub 2  |  sub 3 | Total Marks | Average  |   Result     |\n");
   printf("--------------------------------------------------------------------------------------------------------\n");
    
   for(int i = 0 ;i < noofStu ; i++ ){
          printf("|  %d   |   %10s     |  %6d |     %0.0f |     %0.0f |    %0.0f  |     %3.0f     |   %0.2f   |  %10s |\n",i+1,classRecord->students[i].firstName , classRecord->students[i].rollNo,classRecord->students[i].marks[0],classRecord->students[i].marks[1],classRecord->students[i].marks[2],classRecord->students[i].totalMarks,classRecord->students[i].avg,(classRecord->students[i].isPass == 'P')?"Passed":"Failled");
    }
    printf("-------------------------------------------------------------------------------------------------------\n");
   
    char ch;
    while(1){
        printf("\n\n Press q to exit : ");
        scanf(" %c",&ch);
        if(ch == 'q') break;
    }
}

void findStudent(ClassRecord classRecord){
    system("clear");
   printf("Enter the roll no of student");
   int rollno,noOfStudents = classRecord.noOfStudents;
   scanf("%d",&rollno);
   for(int i=0;i<noOfStudents;i++){
       if(rollno == classRecord.students[i].rollNo){
        printf("\n\n ------- Student Found with Roll no : %d  ------- \n\n",rollno);
           printStudentRecord(classRecord.students[i]);
          return ;
       }
   }
   printf("  ------ No Student found with the Roll No : %d ------ ",rollno);
   char ch;
    while(1){
        printf("\n\n Press q to exit : ");
        scanf(" %c",&ch);
        if(ch == 'q') break;
    }
}

void printStudentRecord(StudentMarkSheet student)
{
    printf("\n  First Name  : %s\n",student.firstName);
    printf("  Last  Name  : %s\n",student.lastName);
    printf("  Roll Number : %d\n",student.rollNo);
    printf("-------------------------------------------------\n");
    printf("| S.no  |  Subject         |     Marks          |\n");
    printf("-------------------------------------------------\n");
    for(int i=0;i<3;i++){
        printf("|  %d    |   Subject 1      |         %0.2f      |\n",i+1,student.marks[i]);
    }
    printf("-------------------------------------------------\n");
    printf("|            Total Marks     :  %0.2f           |\n",student.totalMarks);
    printf("-------------------------------------------------\n");
    printf("                        Average  :   %0.2f \n\n",student.avg); 
    printf("                        Result   :   %s \n\n\n", student.isPass == 'P' ? "PASS" : "FAIL");

}

void printAllStudentsRecord(ClassRecord allstudents){
    system("clear");
    for(int i=0;i<allstudents.noOfStudents;i++){
        printf("\n-------      Student %d     ----------------\n",i+1);
        printStudentRecord(allstudents.students[i]);
    }
    char ch;
    while(1){
        printf("\n\n Press q to exit : ");
        scanf(" %c",&ch);
        if(ch == 'q') break;
    }

}

int stringValidate(char *p) {
    int len = strlen(p);
    
    if (len < 1) {
        return 1; // Empty string = invalid
    }
    // Check all characters are alphabetic
    for (int i = 0; i < len; i++) {
        if (!isalpha(p[i])) {
            return 1; // Non-alphabet = invalid
        }
    }
    // Capitalize the first letter if not already
    if (islower(p[0])) {
        p[0] = toupper(p[0]);
    }

    return 0; // Valid
}
int numberValidate(int num) {
    if (num >= 0 && num <= 999) {
        return 0; // Valid
    }
    return 1; // Invalid
}

int validateMarks(int num) {
    if (num >= 0 && num <= 100) {
        return 0; // Valid
    }
    return 1; // Invalid
}

