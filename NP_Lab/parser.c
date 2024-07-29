#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "course.h"
#include "parser.h"

void parseFile(char *filename, Student **students)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0; // Remove newline character

        // Handle initial database addition
        if (strcmp(line, "# initial addition of database") == 0)
        {
            while (fgets(line, sizeof(line), file) && line[0] != '#')
            {
                line[strcspn(line, "\n")] = 0;
                if (strlen(line) == 0)
                    continue; // Skip empty lines

                // Student details line
                char roll_no[10], name[50];
                float cgpa;
                int num_subjects;
                sscanf(line, "%[^,], %[^,], %f, %d", roll_no, name, &cgpa, &num_subjects);
                addStudent(students, roll_no, name, cgpa, num_subjects);

                // Add courses for the student
                for (int i = 0; i < num_subjects; i++)
                {
                    fgets(line, sizeof(line), file);
                    line[strcspn(line, "\n")] = 0;
                    char course_code[10];
                    int marks;
                    sscanf(line, "%[^,], %d", course_code, &marks);
                    Student *student = findStudent(*students, roll_no);
                    if (student != NULL)
                    {
                        addCourse(student, course_code, marks);
                    }
                }
            }
            printf("Initial Database\n");
            printStudents(*students);
        }

        // Handle adding new students
        else if (strcmp(line, "# add students") == 0)
        {
            while (fgets(line, sizeof(line), file) && line[0] != '#')
            {
                line[strcspn(line, "\n")] = 0;
                if (strlen(line) == 0)
                    continue; // Skip empty lines

                char roll_no[10], name[50];
                float cgpa;
                int num_subjects;
                sscanf(line, "%[^,], %[^,], %f, %d", roll_no, name, &cgpa, &num_subjects);
                addStudent(students, roll_no, name, cgpa, num_subjects);

                // Add courses for the student if available
                for (int i = 0; i < num_subjects; i++)
                {
                    fgets(line, sizeof(line), file);
                    line[strcspn(line, "\n")] = 0;
                    char course_code[10];
                    int marks;
                    sscanf(line, "%[^,], %d", course_code, &marks);
                    Student *student = findStudent(*students, roll_no);
                    if (student != NULL)
                    {
                        addCourse(student, course_code, marks);
                    }
                }
            }
            printf("After adding students\n");
            printStudents(*students);
        }

        // Handle adding a course
        else if (strcmp(line, "# add course") == 0)
        {
            while (fgets(line, sizeof(line), file) && line[0] != '#')
            {
                line[strcspn(line, "\n")] = 0;
                if (strlen(line) == 0)
                    continue; // Skip empty lines

                char roll_no[10], course_code[10];
                int marks;
                sscanf(line, "%[^,], %[^,], %d", roll_no, course_code, &marks);
                Student *student = findStudent(*students, roll_no);
                if (student != NULL)
                {
                    addCourse(student, course_code, marks);
                }
            }
            printf("After adding course\n");
            printStudents(*students);
        }

        // Handle modifying a student
        else if (strcmp(line, "# modify student") == 0)
        {
            while (fgets(line, sizeof(line), file) && line[0] != '#')
            {
                line[strcspn(line, "\n")] = 0;
                if (strlen(line) == 0)
                    continue; // Skip empty lines

                char roll_no[10];
                float cgpa;
                sscanf(line, "%[^,], %f", roll_no, &cgpa);
                Student *student = findStudent(*students, roll_no);
                if (student != NULL)
                {
                    modifyStudent(student, cgpa);
                }
            }
            printf("After modifying student\n");
            printStudents(*students);
        }

        // Handle modifying a course
        else if (strcmp(line, "# modify course") == 0)
        {
            while (fgets(line, sizeof(line), file) && line[0] != '#')
            {
                line[strcspn(line, "\n")] = 0;
                if (strlen(line) == 0)
                    continue; // Skip empty lines

                char roll_no[10], course_code[10];
                int marks;
                sscanf(line, "%[^,], %[^,], %d", roll_no, course_code, &marks);
                Student *student = findStudent(*students, roll_no);
                if (student != NULL)
                {
                    Course *course = student->courses;
                    while (course != NULL)
                    {
                        if (strcmp(course->course_code, course_code) == 0)
                        {
                            modifyCourse(course, marks);
                            break;
                        }
                        course = course->next;
                    }
                }
            }
            printf("After modifying course\n");
            printStudents(*students);
        }

        // Handle deleting a student
        else if (strcmp(line, "# delete student") == 0)
        {
            while (fgets(line, sizeof(line), file) && line[0] != '#')
            {
                line[strcspn(line, "\n")] = 0;
                if (strlen(line) == 0)
                    continue; // Skip empty lines

                char roll_no[10];
                sscanf(line, "%s", roll_no);
                deleteStudent(students, roll_no);
            }
            printf("After deleting student\n");
            printStudents(*students);
        }

        // Handle deleting a course
        else if (strcmp(line, "# delete course") == 0)
        {
            while (fgets(line, sizeof(line), file) && line[0] != '#')
            {
                line[strcspn(line, "\n")] = 0;
                if (strlen(line) == 0)
                    continue; // Skip empty lines

                char roll_no[10], course_code[10];
                sscanf(line, "%[^,], %[^,]", roll_no, course_code);
                Student *student = findStudent(*students, roll_no);
                if (student != NULL)
                {
                    deleteCourse(student, course_code);
                }
            }
            printf("After deleting course\n");
            printStudents(*students);
        }
    }

    fclose(file);
}
