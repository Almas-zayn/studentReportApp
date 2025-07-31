#ifndef __studentMarkSheet__
#define __studentMarkSheet__
#include<stdio.h>
#include <stdlib.h>
typedef struct studentMarkSheet{
        char firstName[50];
        char lastName[50];
        int rollNo;
        float marks[3];
        float totalMarks;
        float avg;
        char isPass; // P-pass,  F-Fail
}StudentMarkSheet;

typedef struct classRecord{
        struct studentMarkSheet *students;
        int noOfStudents;
        int noOfStuPassed;
        float avgOfStudentsPassed;

}ClassRecord;

void printStudentRecord(struct studentMarkSheet student);
void printAllStudentsRecord(ClassRecord allstudents);
void findStudent(ClassRecord classRecord);
int deleteStudentRecord(int rollNo);
void exportStudentReport(ClassRecord classRecord);
int addStudent(ClassRecord *classRecord,FILE *studentFile);


#endif