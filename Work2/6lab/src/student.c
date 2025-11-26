#include "../include/student.h"

#include <ctype.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

double avgMark(Student* st) {
    int sum = 0;

    for (int i = 0; i < 5; ++i) {
        sum += st->marks[i] - '0';
    }

    return (double)sum / 5;
}

void printStudent(const Student* st, FILE* out) {
    if (!st || !out)
        return;

    double avg = avgMark((Student*)st);
    fprintf(out, "%2lu | %-*s | %-*s | %5s | %c %c %c %c %c | %4.2f\n", st->id, 18, st->name, 18,
            st->surname, st->group, st->marks[0], st->marks[1], st->marks[2], st->marks[3],
            st->marks[4], avg);
}

void printStudents(const StudentsData* data, FILE* out) {
    if (!data || data->size == 0) {
        printf("No data\n");
        return;
    }
    if (out != stdout) {
        out = freopen(NULL, "w", out);
        if (!out)
            return;
    }

    fprintf(out,
            "ID | %-18s | %-18s | Group | Marks     | Avg \n"
            "---+--------------------+--------------------+-------+-----------+-----\n",
            "Name", "Surname");

    for (size_t i = 0; i < data->size; ++i) {
        printStudent(data->students[i], out);
    }
    fflush(out);
}

ReturnCode scannerStud(FILE* fData, Student* stud) {
    if (!fData || !stud)
        return INVALID_INPUT_ERR;

    unsigned char* marks = (unsigned char*)malloc(sizeof(unsigned char) * 5);
    if (!marks) {
        return ALLOC_ERR;
    }

    int res =
        fscanf(fData, "%zu %49s %49s %49s %c %c %c %c %c", &stud->id, stud->name, stud->surname,
               stud->group, &marks[0], &marks[1], &marks[2], &marks[3], &marks[4]);

    if (res == EOF) {
        free(marks);
        return EOF_REACHED;
    }

    if (res < 9) {
        free(marks);
        return INVALID_INPUT_ERR;
    }

    stud->marks = marks;

    return OK;
}

ReturnCode readerStud(FILE* fData, StudentsData** studentsData) {
    if (!fData || !studentsData)
        return INVALID_INPUT_ERR;

    StudentsData* stData = NULL;
    ReturnCode err = initStudentsData(&stData);
    if (err != OK)
        return err;

    char chMark;
    unsigned char mark;
    while (1) {
        Student* stud = (Student*)malloc(sizeof(Student));
        if (!stud) {
            free(stData->students);
            free(stData);

            return ALLOC_ERR;
        }

        ReturnCode err = scannerStud(fData, stud);
        if (err == EOF_REACHED) {
            free(stud);
            break;
        }

        if (err != OK) {
            *studentsData = stData;
            free(stud);
            return err;
        }


        for (int i = 0; i < 5; ++i) {
            mark = 0;
            chMark = (char)stud->marks[i];

            if (isdigit(chMark))
                continue;

            if (isalpha(chMark)) {
                chMark = tolower(chMark);
                if (chMark > 'f' || chMark < 'a' || chMark == 'e') {
                    stud->marks[i] = '0';
                    continue;
                }

                switch (chMark) {
                    case 'a':
                        mark = '5';
                        break;
                    case 'b':
                        mark = '4';
                        break;
                    case 'c':
                        mark = '3';
                        break;
                    case 'd':
                        mark = '2';
                        break;
                    case 'f':
                        mark = '1';
                        break;
                }
                stud->marks[i] = mark;
            }
        }

        err = pushbackStudentsData(&stData, stud);
        switch (err) {
            case OK:
                break;
            case ALLOC_ERR:
                fprintf(stderr, "Reallocation error!\n");
                break;
            case INVALID_INPUT_ERR:
                return err;
            default:
                return err;
        }
    }

    *studentsData = stData;

    return OK;
}

void freeStudentsData(StudentsData** data) {
    if (!data || !*data)
        return;

    if ((*data)->students) {
        for (size_t i = 0; i < (*data)->size; ++i) {
            free((*data)->students[i]->marks);
            free((*data)->students[i]);
        }
        free((*data)->students);
        (*data)->students = NULL;
    }

    free((*data));
    *data = NULL;
}

void usage(void) {
    printf("Bad input!\nUsage: <program name> <data file> <trace file>");
    printf("\n\tOR <program name> <data file>");
    return;
}

ReturnCode initStudentsData(StudentsData** studData) {
    if (!studData)
        return INVALID_INPUT_ERR;

    *studData = (StudentsData*)malloc(sizeof(StudentsData));
    if (!*studData) {
        return ALLOC_ERR;
    }


    (*studData)->size = 0;
    (*studData)->capacity = POOL;
    (*studData)->students = (Student**)malloc(sizeof(Student*) * (*studData)->capacity);
    if (!(*studData)->students) {
        free((*studData));
        return ALLOC_ERR;
    }
    return OK;
}

ReturnCode pushbackStudentsData(StudentsData** studData, Student* st) {
    if (!studData || !*studData) {
        printf("Pointers error!\n");
        return INVALID_INPUT_ERR;
    }

    if ((*studData)->size >= (*studData)->capacity) {

        size_t newCap = (*studData)->capacity * 2;

        Student** tmp = realloc((*studData)->students, sizeof(Student*) * newCap);
        if (!tmp) {
            printf("Allocation error!\n");
            return ALLOC_ERR;
        }

        (*studData)->students = tmp;
        (*studData)->capacity = newCap;
    }
    (*studData)->students[(*studData)->size++] = st;

    return OK;
}

ReturnCode validateNumber(const char* numberStr, int* number) {
    char* endptr;
    long num = strtol(numberStr, &endptr, 10);

    if (*endptr != '\0') {
        return INVALID_INPUT_ERR;
    }
    if (num > INT_MAX) {
        return OVERFLOW_ERR;
    }
    *number = (int)num;
    return OK;
}