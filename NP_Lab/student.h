#ifndef STUDENT_H
#define STUDENT_H

typedef struct Course
{
    char course_code[10];
    int marks;
    struct Course *prev;
    struct Course *next;
} Course;

typedef struct Student
{
    char roll_no[10];
    char name[50];
    float cgpa;
    int num_subjects;
    Course *courses;
    struct Student *prev;
    struct Student *next;
} Student;

// Student related functions
Student *createStudent(char *roll_no, char *name, float cgpa, int num_subjects);
void addStudent(Student **head, char *roll_no, char *name, float cgpa, int num_subjects);
Student *findStudent(Student *head, char *roll_no);
void modifyStudent(Student *student, float cgpa);
void deleteStudent(Student **head, char *roll_no);
void printStudents(Student *head);
void freeStudents(Student *head);

#endif // STUDENT_H
