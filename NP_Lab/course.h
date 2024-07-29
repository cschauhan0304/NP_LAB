#ifndef COURSE_H
#define COURSE_H

#include "student.h"

// Course related functions
Course *createCourse(char *course_code, int marks);
void addCourse(Student *student, char *course_code, int marks);
void modifyCourse(Course *course, int marks);
void deleteCourse(Student *student, char *course_code);

#endif // COURSE_H
