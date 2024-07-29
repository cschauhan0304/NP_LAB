#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "course.h"

// Create a new course node
Course *createCourse(char *course_code, int marks)
{
    Course *new_course = (Course *)malloc(sizeof(Course));
    strcpy(new_course->course_code, course_code);
    new_course->marks = marks;
    new_course->prev = NULL;
    new_course->next = NULL;
    return new_course;
}

// Add a course to a student's course doubly linked list
void addCourse(Student *student, char *course_code, int marks)
{
    Course *new_course = createCourse(course_code, marks);
    new_course->next = student->courses;
    if (student->courses != NULL)
    {
        student->courses->prev = new_course;
    }
    student->courses = new_course;
    student->num_subjects++;
}

// Modify a course's marks
void modifyCourse(Course *course, int marks)
{
    course->marks = marks;
}

// Delete a course from a student's course doubly linked list
void deleteCourse(Student *student, char *course_code)
{
    Course *current = student->courses;
    while (current != NULL)
    {
        if (strcmp(current->course_code, course_code) == 0)
        {
            if (current->prev != NULL)
            {
                current->prev->next = current->next;
            }
            else
            {
                student->courses = current->next;
            }
            if (current->next != NULL)
            {
                current->next->prev = current->prev;
            }
            free(current);
            student->num_subjects--;
            return;
        }
        current = current->next;
    }
}
