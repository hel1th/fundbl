#include "../include/sort_student.h"

#include <stdlib.h>
#include <string.h>

// ReturnCode StudSortById(StudentsData* stData) {
//     if (!stData || stData->size == 0 || !stData->students)
//         return INVALID_INPUT_ERR;

//     qsort(stData->students, stData->size, sizeof(Student*), StudCmpById);

//     return OK;
// }
// ReturnCode StudSortByName(StudentsData* stData) {
//     if (!stData || stData->size == 0 || !stData->students)
//         return INVALID_INPUT_ERR;

//     qsort(stData->students, stData->size, sizeof(Student*), StudCmpByName);

//     return OK;
// }
// ReturnCode StudSortBySurname(StudentsData* stData) {
//     if (!stData || stData->size == 0 || !stData->students)
//         return INVALID_INPUT_ERR;

//     qsort(stData->students, stData->size, sizeof(Student*), StudCmpBySurname);

//     return OK;
// }
// ReturnCode StudSortByGroup(StudentsData* stData) {
//     if (!stData || stData->size == 0 || !stData->students)
//         return INVALID_INPUT_ERR;

//     qsort(stData->students, stData->size, sizeof(Student*), StudCmpByGroup);

//     return OK;
// }
int StudCmpById(const void* a, const void* b) {
    const Student* s1 = *(const Student**)a;
    const Student* s2 = *(const Student**)b;
    
    return (s1->id > s2->id) - (s1->id < s2->id);
}

int StudCmpByName(const void* a, const void* b) {
    const Student* s1 = *(const Student**)a;
    const Student* s2 = *(const Student**)b;

    return strcmp(s1->name, s2->name);
}

int StudCmpBySurname(const void* a, const void* b) {
    const Student* s1 = *(const Student**)a;
    const Student* s2 = *(const Student**)b;

    return strcmp(s1->surname, s2->surname);
}

int StudCmpByGroup(const void* a, const void* b) {
    const Student* s1 = *(const Student**)a;
    const Student* s2 = *(const Student**)b;

    return strcmp(s1->group, s2->group);
}

ReturnCode StudentSort(SortChoice srtChoice, StudentsData* stData) {
    if (!stData || stData->size == 0 || !stData->students)
        return INVALID_INPUT_ERR;

    switch (srtChoice) {
        case SORT_ID:
            qsort(stData->students, stData->size, sizeof(Student*), StudCmpById);
            break;

        case SORT_NAME:
            qsort(stData->students, stData->size, sizeof(Student*), StudCmpByName);
            break;

        case SORT_SURNAME:
            qsort(stData->students, stData->size, sizeof(Student*), StudCmpBySurname);
            break;

        case SORT_GROUP:
            qsort(stData->students, stData->size, sizeof(Student*), StudCmpByGroup);
            break;
    }

    return OK;
}