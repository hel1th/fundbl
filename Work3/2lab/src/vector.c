#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VECTOR_TYPE int
#include "../include/vector.h"

Vector create_vector(size_t initial_capacity, VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE),
                     void (*DeleteFunc)(VECTOR_TYPE)) {
    Vector v;
    v.size = 0;
    v.capacity = initial_capacity;
    v.CopyVoidPtr = CopyFunc;
    v.DeleteVoidPtr = DeleteFunc;

    v.data = (VECTOR_TYPE*)malloc(sizeof(VECTOR_TYPE) * v.capacity);
    if (!v.data || !v.DeleteVoidPtr || !v.CopyVoidPtr) {
        fprintf(stderr, "Error: NULL pointer passed\n");
        VECTOR_NULL(v);
        return v;
    }

    return v;
}

void erase_vector(Vector* v) {
    if (!v)
        return;

    if (v->DeleteVoidPtr && v->data) {
        for (size_t i = 0; i < v->size; i++) {
            v->DeleteVoidPtr(v->data[i]);
        }
    }
    free(v->data);
    VECTOR_NULL(*v);
}

int is_equal_vector(const Vector* v1, const Vector* v2) {
    if (!v1 || !v2) {
        fprintf(stderr, "Error: NULL pointer passed\n");
        return 0;
    }
    int cmp = memcmp(v1->data, v2->data,
                     ((v1->size < v2->size) ? v1->size : v2->size) * sizeof(VECTOR_TYPE));
    if (cmp == 0)
        return (v1->size > v2->size) - (v1->size < v2->size);

    return cmp;
}

void copy_vector(Vector* dest, const Vector* src) {
    if (!dest || !src) {
        fprintf(stderr, "Error: NULL pointer passed\n");
        return;
    }
    if (!src->data || !src->CopyVoidPtr) {
        fprintf(stderr, "Error: NULL pointer passed\n");
        return;
    }

    erase_vector(dest);

    dest->CopyVoidPtr = src->CopyVoidPtr;
    dest->DeleteVoidPtr = src->DeleteVoidPtr;

    dest->capacity = src->size > 0 ? src->size : POOL;
    dest->data = (VECTOR_TYPE*)malloc(dest->capacity * sizeof(VECTOR_TYPE));
    if (!dest->data) {
        fprintf(stderr, "Error: Failed to allocate memory for new vector\n");
        return;
    }

    for (size_t i = 0; i < src->size; ++i) {
        dest->data[i] = src->CopyVoidPtr(src->data[i]);
    }
    dest->size = src->size;
    return;
}

Vector* copy_vector_new(const Vector* src) {
    if (!src) {
        fprintf(stderr, "Error: NULL pointer passed\n");
        return NULL;
    }

    Vector* new = (Vector*)malloc(sizeof(Vector));
    if (!new) {
        fprintf(stderr, "Error: Failed to allocate memory for new vector\n");
        return NULL;
    }

    VECTOR_NULL(*new);
    copy_vector(new, src);

    if (!new->data) {
        free(new);
        return NULL;
    }

    return new;
}

void push_back_vector(Vector* v, VECTOR_TYPE value) {
    if (!v || !v->data) {
        fprintf(stderr, "Error: NULL pointer passed\n");
        return;
    }

    if (v->size >= v->capacity) {
        VECTOR_TYPE* tmp =
            (VECTOR_TYPE*)realloc(v->data, sizeof(VECTOR_TYPE) * v->capacity * GROWTH_FACTOR);

        if (!tmp) {
            fprintf(stderr, "Error: Failed to reallocate memory for vector\n");
            return;
        }

        v->data = tmp;
        v->capacity *= GROWTH_FACTOR;
    }

    v->data[(v->size)++] = value;
    return;
}

void delete_at_vector(Vector* v, size_t index) {
    if (!v) {
        fprintf(stderr, "Error: NULL pointer passed\n");
        return;
    }

    if (index >= v->size || index < 0) {
        fprintf(stderr, "Error: Index %zu out of bounds (size: %zu)\n", index, v->size);
        return;
    }

    if (v->DeleteVoidPtr) {
        v->DeleteVoidPtr(v->data[index]);
    }

    for (size_t i = index; i < v->size - 1; ++i) {
        v->data[i] = v->data[i + 1];
    }

    --(v->size);
}

VECTOR_TYPE get_at_vector(const Vector* v, size_t index) {
    if (!v) {
        fprintf(stderr, "Error: Vector is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (index >= v->size) {
        fprintf(stderr, "Error: Index %zu out of bounds (size: %zu)\n", index, v->size);
        exit(EXIT_FAILURE);
    }

    return v->data[index];
}

void delete_vector(Vector* v) {
    if (!v) {
        fprintf(stderr, "Error: Vector is NULL\n");
        return;
    }

    erase_vector(v);
}