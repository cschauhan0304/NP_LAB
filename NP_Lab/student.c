#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "course.h"

// Create a new student node
Student *createStudent(char *roll_no, char *name, float cgpa, int num_subjects)
{
    Student *new_student = (Student *)malloc(sizeof(Student));
    strcpy(new_student->roll_no, roll_no);
    strcpy(new_student->name, name);
    new_student->cgpa = cgpa;
    new_student->num_subjects = num_subjects;
    new_student->courses = NULL;
    new_student->prev = NULL;
    new_student->next = NULL;
    return new_student;
}

// Add a student to the doubly linked list
void addStudent(Student **head, char *roll_no, char *name, float cgpa, int num_subjects)
{
    Student *new_student = createStudent(roll_no, name, cgpa, num_subjects);
    new_student->next = *head;
    if (*head != NULL)
    {
        (*head)->prev = new_student;
    }
    *head = new_student;
}

// Find a student by roll number
Student *findStudent(Student *head, char *roll_no)
{
    Student *current = head;
    while (current != NULL)
    {
        if (strcmp(current->roll_no, roll_no) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Modify a student's CGPA
void modifyStudent(Student *student, float cgpa)
{
    student->cgpa = cgpa;
}

// Delete a student from the doubly linked list
void deleteStudent(Student **head, char *roll_no)
{
    Student *current = *head;
    while (current != NULL)
    {
        if (strcmp(current->roll_no, roll_no) == 0)
        {
            if (current->prev != NULL)
            {
                current->prev->next = current->next;
            }
            else
            {
                *head = current->next;
            }
            if (current->next != NULL)
            {
                current->next->prev = current->prev;
            }
            Course *course = current->courses;
            while (course != NULL)
            {
                Course *temp = course;
                course = course->next;
                free(temp);
            }
            free(current);
            return;
        }
        current = current->next;
    }
}

// Print all students and their courses
void printStudents(Student *head)
{
    Student *current = head;
    while (current != NULL)
    {
        printf("Student Roll No: %s, Name: %s, CGPA: %.2f, Number of Subjects: %d\n", current->roll_no, current->name, current->cgpa, current->num_subjects);
        Course *course = current->courses;
        while (course != NULL)
        {
            printf("\tCourse Code: %s, Marks: %d\n", course->course_code, course->marks);
            course = course->next;
        }
        current = current->next;
    }
}

// Free memory allocated for students and their courses
void freeStudents(Student *head)
{
    Student *current = head;
    while (current != NULL)
    {
        Student *temp = current;
        current = current->next;
        Course *course = temp->courses;
        while (course != NULL)
        {
            Course *temp_course = course;
            course = course->next;
            free(temp_course);
        }
        free(temp);
    }
}
