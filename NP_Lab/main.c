#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "course.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <input_filename>\n", argv[0]);
        return 1;
    }

    Student *students = NULL;
    parseFile(argv[1], &students);
    printStudents(students);
    freeStudents(students);

    return 0;
}
