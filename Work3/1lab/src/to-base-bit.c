#include "../include/to-base-bit.h"

#include "../../macro-include/stack.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

STACK_DEF(Bity, char)

uint32_t bitIncr(uint32_t x) {
    uint32_t carry = 1, tmp;
    while (carry) {
        tmp = carry & x;
        x ^= carry;
        carry = tmp << 1;
    }
    return x;
}

uint32_t bitDecr(uint32_t x) {
    uint32_t borrow = 1, tmp;
    while (borrow) {
        tmp = (~x) & borrow;
        x ^= borrow;
        borrow = tmp << 1;
    }
    return x;
}

uint32_t makeMask(uint32_t r) {
    uint32_t tmp = 1 << r;
    uint32_t mask = bitDecr(tmp);

    return mask;
}

void toBase2RBit(uint32_t n, int r, char** res) {
    if (r < 1 || 5 < r) {
        *res = NULL;
        return;
    }
    char* out = malloc(33);
    if (!out) {
        *res = NULL;
        return;
    }

    if (n == 0) {
        out[0] = '0';
        out[1] = '\0';
        *res = out;
        return;
    }

    Bity_stack* stack = NULL;
    Stack_Bity_init(&stack);

    const char digits[] = "0123456789abcdefghijklmnopqrstuv";

    uint32_t mask = makeMask(r);

    uint32_t idx = 0;
    while (n != 0) {
        uint32_t chunk = n & mask;
        Stack_Bity_push(stack, digits[chunk]);
        n >>= r;
    }

    char ch;
    StackStatus err = STACK_OK;
    while (err == STACK_OK && (err = Stack_Bity_peek(stack, &ch)) != STACK_EMPTY) {
        out[idx] = ch;
        idx = bitIncr(idx);
        err = Stack_Bity_pop(stack);
    }
    out[idx] = '\0';
    *res = out;
    Stack_Bity_destroy(&stack);
    return;
}