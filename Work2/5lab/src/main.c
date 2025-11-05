#include "../include/functions.h"

#include <stdio.h>

int main() {
    char fileInName[1000] = {[0] = '\0'};
    char fileOutName[1000] = {[0] = '\0'};


    FILE *fileIn, *fileOut;
    printf("Enter file input name: ");
    scanf("%s", fileInName);
    if (!(fileIn = fopen(fileInName, "r"))) {
        printf("Error occured during opening file %s", fileInName);
        return -1;
    }

    printf("\nEnter file output name: ");
    scanf("%s", fileOutName);
    if (!(fileOut = fopen(fileOutName, "w"))) {
        printf("Error occured during opening file %s", fileOutName);
        fclose(fileIn);
        return -1;
    }

    refactor(fileIn, fileOut);
}