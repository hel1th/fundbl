#include "../include/interactive.h"

#include <stdlib.h>
#include <string.h>

typedef enum SortChoice {
    SORT_ID,
    SORT_NAME,
    SORT_SURNAME,
    SORT_GROUP,
} SortChoice;

int StudCmpById(const void* s1, const void* s2);

// ReturnCode StudSortById(StudentsData* stData);

int StudCmpByName(const void* s1, const void* s2);

// ReturnCode StudSortByName(StudentsData* stData);

int StudCmpBySurname(const void* s1, const void* s2);
// ReturnCode StudSortBySurname(StudentsData* stData);

int StudCmpByGroup(const void* s1, const void* s2);

// ReturnCode StudSortByGroup(StudentsData* stData);

ReturnCode StudentSort(SortChoice srtChoice, StudentsData* stData);