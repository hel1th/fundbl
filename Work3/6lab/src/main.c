#include "../include/vaidate-parentheses.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* text[] = {"{}", "", "djsalidj", "adkal{sdasdmaslkdav sd<sdaklsda>sdijasoidja()}",
                          "adkal{sdasdmaslkdav sd<sdaklsda>sdijasoidja(}"};

    for (int i = 0; i < 10; ++i) {
        ReturnCode status = check_brackets(text[i]);

        switch (status) {
            case BALANCED:
                printf("%2d. %s IS balanced\n", i, text[i]);
                break;

            case NOT_BALANCED:
                printf("%2d. %s is NOT balanced\n", i, text[i]);
                break;

            default:
                printf("Something went wrong\n");
        }
    }
}