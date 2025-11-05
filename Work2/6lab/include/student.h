#ifndef STUDENT_H
#define STUDENT_H


#include <stddef.h>
#include <stdio.h>

#define NAME_LEN 50
#define GROUP_LEN 50
#define POOL 10

typedef enum {
    OK = 0,
    INVALID_INPUT_ERR,
    FILE_OPEN_ERR,
    ALLOC_ERR,
    EOF_REACHED,
} ReturnCode;

typedef struct Student_ {
    size_t id;
    char name[NAME_LEN];
    char surname[NAME_LEN];
    char group[GROUP_LEN];
    unsigned char* marks;
} Student;

typedef struct StudentsData_ {
    Student** students;
    size_t size;
    size_t capacity;
} StudentsData;

ReturnCode readerStud(FILE* fData, StudentsData** studentsData);

void printStudents(const StudentsData* data, FILE* out);

void freeStudentsData(StudentsData** data);

double avgMark(Student* st);
void usage(void);

ReturnCode initStudentsData(StudentsData** studData);
// ReturnCode reallocStudentsData(StudentsData** studData);
ReturnCode pushbackStudentsData(StudentsData** studData, Student* st);
#endif // STUDENT_H