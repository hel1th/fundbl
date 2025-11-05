#include "../include/interactive.h"
#include "../include/student.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    // ./prog.out stud.txt [trace.txt]
    if (argc > 3 || argc < 2) {
        usage();
        return INVALID_INPUT_ERR;
    }


    FILE* dataFile = fopen(argv[1], "r");
    if (!dataFile) {
        printf("Error occured while opening dataFile: %s!", argv[1]);
        return FILE_OPEN_ERR;
    }


    FILE* traceFile;

    if (argc == 3) { // if there is no traceFile in argv then it will be replaced with stdin
        traceFile = fopen(argv[2], "w");
        if (!traceFile) {
            printf("Error occured while opening traceFile: %s!", argv[2]);
            return FILE_OPEN_ERR;
        }

    } else {
        traceFile = stdout;
    }


    StudentsData* stado = NULL;

    if (readerStud(dataFile, &stado) != OK) {
        if (argc == 3)
            fclose(traceFile);
        printf("Error occured during reading %s!\n", argv[1]);
        return INVALID_INPUT_ERR;
    }


    interactiveMode(stado, traceFile);


    freeStudentsData(&stado);
    if (argc == 3)
        fclose(traceFile);
    return OK;
}