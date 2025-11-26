

#include "../include/search_student.h"
#include "../include/sort_student.h"
#include "../include/student.h"

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMenu(void) {
    printf("===== Menu =====\n");
    printf("%d. Search by ...\n", SEARCH_CHOICE);
    printf("%d. Sort by ...\n", SORT_CHOICE);
    printf("%d. Show Leaderboard\n", LEADERBOARD_CHOICE);
    printf("%d. Show all of the students\n", SHOW_ALL_CHOICE);
    printf("%d. Exit\n", EXIT_CHOICE);
    printf("================\n");
    return;
}

void printSort(void) {
    printf("\t===== Sort by =====\n");
    printf("\t1. ID\n");
    printf("\t2. Name\n");
    printf("\t3. Surname\n");
    printf("\t4. Group\n");
    printf("\t===================\n\t");
    return;
}

void printSearch(void) {
    printf("\t===== Search by =====\n");
    printf("\t1. ID\n");
    printf("\t2. Name\n");
    printf("\t3. Surname\n");
    printf("\t4. Group\n");
    printf("\t=====================\n\t");
    return;
}

MenuChoice handleMenu(void) {
    char number[33] = {[0] = '\0'};
    int choice;
    while (1) {
        printMenu();
        if (scanf("%32s", number) != 1)
            continue;

        if (validateNumber(number, &choice) != OK) {
            continue;
        }

        if (choice < EXIT_CHOICE || SHOW_ALL_CHOICE < choice)
            continue;

        return (MenuChoice)choice;
    }
}

SearchChoice handleSearch(void) {
    char numberStr[33] = {[0] = '\0'};
    int choice;
    while (1) {
        printSearch();
        if (scanf("%32s", numberStr) != 1)
            continue;

        if (validateNumber(numberStr, &choice) != OK) {
            continue;
        }
        choice -= 1;
        if (choice < SEARCH_ID || SEARCH_GROUP < choice)
            continue;

        return (SearchChoice)choice;
    }
}

SortChoice handleSort(void) {
    char number[33] = {[0] = '\0'};
    int choice;
    while (1) {
        printSort();
        if (scanf("%32s", number) != 1)
            continue;

        if (validateNumber(number, &choice) != OK) {
            continue;
        }

        choice -= 1;
        if (choice < SORT_ID || SORT_GROUP < choice)
            continue;

        return (SortChoice)choice;
    }
}

void interactiveMode(StudentsData* stData, FILE* output) {
    SortChoice sortChoice;
    SearchChoice searchChoice;
    StudentsData* newStudData = NULL;
    ReturnCode err;
    while (1) {

        MenuChoice menuChoice = handleMenu();
        switch (menuChoice) {
            case EXIT_CHOICE:
                printf("Exiting...\n");
                return;

            case SEARCH_CHOICE:
                searchChoice = handleSearch();

                err = findByChoice(searchChoice, stData, &newStudData);
                if (err != OK)
                    return;

                printStudents(newStudData, output);
                free(newStudData);

                continue;

            case SORT_CHOICE:
                sortChoice = handleSort();

                err = StudentSort(sortChoice, stData);
                if (err != OK)
                    return;

                printStudents(stData, output);
                continue;


            case LEADERBOARD_CHOICE:
                newStudData = NULL;
                findLeaderboard(stData, &newStudData);
                if (err != OK)
                    return;

                printStudents(newStudData, output);

                free(newStudData);
                continue;

            case SHOW_ALL_CHOICE:
                printStudents(stData, output);
                continue;
        }
    }
}
