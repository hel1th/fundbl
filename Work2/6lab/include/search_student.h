#include "student.h"

#include <stdlib.h>

typedef enum SearchChoice {
    SEARCH_ID,
    SEARCH_NAME,
    SEARCH_SURNAME,
    SEARCH_GROUP,
} SearchChoice;

ReturnCode findLeaderboard(StudentsData* stData, StudentsData** leadDataPtr);
ReturnCode findByChoice(SearchChoice searchBy, StudentsData* stData, StudentsData** leadDataPtr);