#ifndef LIVER_H
#define LIVER_H


#include <stddef.h>

// мы живем в идеальном мире, где в каждом месяце по 30 дней, а вискосных лет не существует
typedef struct Date_ {
    unsigned int day;
    unsigned int month;
    unsigned int year;
} Date;

typedef struct Liver_ {
    size_t id;
    char* surname;
    char* name;
    char* patronim;
    Date dateOfBirth;
    char sex;
    double avg_income;
} Liver;


#endif // LIVER_H