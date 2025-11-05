#include "student.h"

#include <stdio.h>

typedef enum InterChoice {
    EXIT_CHOICE = 0,
    SEARCH_CHOICE,
    SORT_CHOICE,
    LEADERBOARD_CHOICE,
    SHOW_ALL_CHOICE
} MenuChoice;

void interactiveMode(StudentsData* stData, FILE* output);