#include "../../macro-include/stack.h"
#include "../include/to-base-bit.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void) {

    char* res = "";

    int r;
    uint32_t n;

    uint32_t nArr[] = {0u, 1u, 32u, 21341u, UINT32_MAX};
    int rArr[] = {-1, 0, 1, 2, 3, 4, 5, 6};
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 8; ++j) {
            n = nArr[i];
            r = rArr[j];

            toBase2RBit(n, r, &res);
            printf("============\n");
            printf("n = %u\nr = %d\n", n, r);

            if (res) {
                printf("res = %s\n", res);
                free(res);
                res = NULL;
            } else {
                printf("res = NULL (invalid r)\n");
            }
        }
    }
}