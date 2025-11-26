#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  STACK_OK = 0,
  STACK_ALLOC_ERR,
  STACK_NULL_PTR_ERR,
  STACK_EMPTY,
} StackStatus;

#define POOL 10
#define GROW_FACTOR 2
#define STACK_DEF(SNAME, STYPE)                                                \
                                                                               \
  typedef struct {                                                             \
    STYPE *data;                                                               \
    size_t size;                                                               \
    size_t capacity;                                                           \
  } SNAME##_stack;                                                             \
                                                                               \
  static inline StackStatus Stack_##SNAME##_init(SNAME##_stack **s) {          \
    if (!s)                                                                    \
      return STACK_NULL_PTR_ERR;                                               \
                                                                               \
    SNAME##_stack *stack = (SNAME##_stack *)malloc(sizeof(SNAME##_stack));     \
    if (!stack)                                                                \
      return STACK_ALLOC_ERR;                                                  \
                                                                               \
    stack->size = 0;                                                           \
    stack->capacity = POOL;                                                    \
    stack->data = (STYPE *)malloc(sizeof(STYPE) * stack->capacity);            \
    if (!stack->data) {                                                        \
      free(stack);                                                             \
      return STACK_ALLOC_ERR;                                                  \
    }                                                                          \
    *s = stack;                                                                \
    return STACK_OK;                                                           \
  }                                                                            \
                                                                               \
  static inline StackStatus Stack_##SNAME##_destroy(SNAME##_stack **s) {       \
    if (!s || !*s) {                                                           \
      return STACK_NULL_PTR_ERR;                                               \
    }                                                                          \
    free((*s)->data);                                                          \
    free(*s);                                                                  \
    *s = NULL;                                                                 \
    return STACK_OK;                                                           \
  }                                                                            \
                                                                               \
  static inline StackStatus Stack_##SNAME##_push(SNAME##_stack *s,             \
                                                 STYPE elem) {                 \
    if (!s)                                                                    \
      return STACK_NULL_PTR_ERR;                                               \
                                                                               \
    if (s->size >= s->capacity) {                                              \
      STYPE *tmp = (STYPE *)realloc(s->data, sizeof(STYPE) * s->capacity *     \
                                                 GROW_FACTOR);                 \
      if (!tmp) {                                                              \
        return STACK_ALLOC_ERR;                                                \
      }                                                                        \
      s->data = tmp;                                                           \
      s->capacity *= 2;                                                        \
    }                                                                          \
    s->data[(s->size)++] = elem;                                               \
    return STACK_OK;                                                           \
  }                                                                            \
                                                                               \
  static inline StackStatus Stack_##SNAME##_empty(SNAME##_stack *s,            \
                                                  int *isEmpty) {              \
    if (!s || !isEmpty)                                                        \
      return STACK_NULL_PTR_ERR;                                               \
                                                                               \
    *isEmpty = s->size > 0 ? 0 : 1;                                            \
    return STACK_OK;                                                           \
  }                                                                            \
                                                                               \
  static inline StackStatus Stack_##SNAME##_peek(SNAME##_stack *s,             \
                                                 STYPE *resVal) {              \
    if (!s || !resVal)                                                         \
      return STACK_NULL_PTR_ERR;                                               \
                                                                               \
    int empt = 1;                                                              \
    StackStatus err = Stack_##SNAME##_empty(s, &empt);                         \
                                                                               \
    if (err != STACK_OK) {                                                     \
      return err;                                                              \
    }                                                                          \
    if (empt) {                                                                \
      return STACK_EMPTY;                                                      \
    }                                                                          \
                                                                               \
    *resVal = s->data[s->size - 1];                                            \
    return STACK_OK;                                                           \
  }                                                                            \
                                                                               \
  static inline StackStatus Stack_##SNAME##_pop(SNAME##_stack *s) {            \
    int empt = 0;                                                              \
    if (!s)                                                                    \
      return STACK_NULL_PTR_ERR;                                               \
                                                                               \
    StackStatus err = Stack_##SNAME##_empty(s, &empt);                         \
    if (err != STACK_OK) {                                                     \
      return err;                                                              \
    }                                                                          \
    if (empt) {                                                                \
      return STACK_EMPTY;                                                      \
    }                                                                          \
                                                                               \
    s->size -= 1;                                                              \
    return STACK_OK;                                                           \
  }

#endif // STACK_H
