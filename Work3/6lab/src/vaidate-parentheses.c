#include "../include/vaidate-parentheses.h"

#include "../../macro-include/stack.h"

#include <string.h>

STACK_DEF(Char, char)

ReturnCode check_brackets(const char* str) {
    if (!str) {
        return NULL_PTR_ERR;
    }
    char *cur, top;
    int empty = 1;

    Char_stack* stack = NULL;
    Stack_Char_init(&stack);

    const char* BRACKETS = "()[]{}<>";

    while (*str) {
        cur = strpbrk(str, BRACKETS);

        if (cur == NULL)
            break;

        str += (str - cur);

        switch (*str) {
            case '[':
            case '(':
            case '{':
            case '<':
                Stack_Char_push(stack, *str);
                ++str;
                break;
            case ']':
                Stack_Char_peek(stack, &top);
                if (top != '[') {
                    Stack_Char_destroy(&stack);
                    return NOT_BALANCED;
                }
                Stack_Char_pop(stack);
                ++str;
                break;

            case ')':
                Stack_Char_peek(stack, &top);
                if (top != '(') {
                    Stack_Char_destroy(&stack);
                    return NOT_BALANCED;
                }
                Stack_Char_pop(stack);
                ++str;
                break;

            case '}':
                Stack_Char_peek(stack, &top);
                if (top != '{') {
                    Stack_Char_destroy(&stack);
                    return NOT_BALANCED;
                }
                Stack_Char_pop(stack);
                ++str;
                break;

            case '>':
                Stack_Char_peek(stack, &top);
                if (top != '<') {
                    Stack_Char_destroy(&stack);
                    return NOT_BALANCED;
                }
                Stack_Char_pop(stack);
                ++str;
                break;
        }
    }


    StackStatus err = Stack_Char_empty(stack, &empty);
    if (err)
        return STACK_ERR;

    if (empty) {
        return BALANCED;
    } else {
        return NOT_BALANCED;
    }
}