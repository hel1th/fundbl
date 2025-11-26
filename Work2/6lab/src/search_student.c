#include "../include/search_student.h"

#include "../include/student.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

ReturnCode findLeaderboard(StudentsData* stData, StudentsData** leadDataPtr) {
    if (!stData || !leadDataPtr) {
        return INVALID_INPUT_ERR;
    }
    double commonAvgMark = 0;
    double curAvgMark = 0;

    StudentsData* leadData = NULL;
    ReturnCode err = initStudentsData(&leadData);
    if (err != OK)
        return err;


    for (size_t i = 0; i < stData->size; i++) {
        commonAvgMark += avgMark(stData->students[i]);
    }
    commonAvgMark /= stData->size;


    for (size_t i = 0; i < stData->size; i++) {
        curAvgMark = avgMark(stData->students[i]);

        if (curAvgMark <= commonAvgMark) {
            continue;
        }
        err = pushbackStudentsData(&leadData, stData->students[i]);
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


    *leadDataPtr = leadData;
    return OK;
}

ReturnCode findByChoice(SearchChoice searchBy, StudentsData* stData, StudentsData** leadDataPtr) {
    if (!stData) {
        return INVALID_INPUT_ERR;
    }
    size_t intKey;
    int idToFind = 0;
    char strKey[NAME_LEN];

    int red = 0;
    StudentsData* foundStudents = NULL;
    ReturnCode err = initStudentsData(&foundStudents);
    if (err != OK) {
        return err;
    }


    switch (searchBy) {
        case SEARCH_ID:
            char numStr[33] = {[0] = '\0'};

            do {

                idToFind = 0;
                scanf("%32s", numStr);
            } while (validateNumber(numStr, &idToFind) != OK);

            for (size_t i = 0; i < stData->size; ++i) {
                if (idToFind == stData->students[i]->id) {
                    pushbackStudentsData(&foundStudents, stData->students[i]);
                }
            }
            break;

        case SEARCH_NAME:
            red = 0;
            while (red != 1) {
                printf("Enter the name to find for: ");
                red = scanf("%49s", strKey);
            }
            for (size_t i = 0; i < stData->size; ++i) {
                if (strcmp(strKey, stData->students[i]->name) == 0) {
                    pushbackStudentsData(&foundStudents, stData->students[i]);
                }
            }
            break;

        case SEARCH_SURNAME:
            red = 0;
            while (red != 1) {
                printf("Enter the surname to find for: ");
                red = scanf("%49s", strKey);
            }
            for (size_t i = 0; i < stData->size; ++i) {
                if (strcmp(strKey, stData->students[i]->surname) == 0) {
                    pushbackStudentsData(&foundStudents, stData->students[i]);
                }
            }
            break;

        case SEARCH_GROUP:
            red = 0;
            while (red != 1) {
                printf("Enter the group to find for: ");
                red = scanf("%49s", strKey);
            }
            for (size_t i = 0; i < stData->size; ++i) {
                if (strcmp(strKey, stData->students[i]->group) == 0) {
                    pushbackStudentsData(&foundStudents, stData->students[i]);
                }
            }
            break;
    }

    *leadDataPtr = foundStudents;
    return OK;
}
