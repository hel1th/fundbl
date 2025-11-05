#include "../include/finite.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


int main(void) {
    ReturnCode status;
    int n = 4;
    double list[] = {
        1.0 / 3.0,
        0.125,
        0.5,
        1.0 / 12,
    };
    int number_system = 10;
    bool* result;

    status = areFinite(number_system, &result, n, list[0], list[1], list[2], list[3], list[4]);

    switch (status) {
        case OK:
            break;

        case ALLOC_ERR:
            printf("Error during allocating memmory!\n");
            return ALLOC_ERR;

        case CONVERT_ERR:
            printf("Error occured while converting numbers!\n");
            return CONVERT_ERR;

        case OVERFLOW_ERR:
            printf("OVERFLOW!\n");
            return OVERFLOW_ERR;

        case UNKNOWN_ERR:
            printf("Unknown error occured!\n");
            return UNKNOWN_ERR;
    }

    for (int i = 0; i < n; ++i) {
        printf("Число %lf - ", list[i]);

        if (result[i]) {
            printf("КОНЕЧНО ");
        } else {
            printf("БЕСконечно ");
        }

        printf("в base %d\n", number_system);
    }
    free(result);
    return OK;
}
