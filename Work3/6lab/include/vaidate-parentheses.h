#ifndef VAILDATE_PAR
#define VAILDATE_PAR

typedef enum {
    NOT_BALANCED = -1,
    BALANCED,
    OK,
    NULL_PTR_ERR,
    STACK_ERR,
} ReturnCode;

ReturnCode check_brackets(const char* str);

#endif // VAILDATE_PAR


