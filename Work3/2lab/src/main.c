#include <stdio.h>
#include <stdlib.h>


#define VECTOR_TYPE int
#include "../include/vector.h"

int copy_int(int x) {
    return x;
}

void delete_int(int x) {

    (void)x;
}

int main() {

    Vector v = create_vector(5, copy_int, delete_int);

    printf("Pushing elements...\n");
    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    push_back_vector(&v, 40);
    push_back_vector(&v, 50);

    printf("Vector size: %zu, capacity: %zu\n", v.size, v.capacity);


    printf("Elements: ");
    for (size_t i = 0; i < v.size; i++) {
        printf("%d ", get_at_vector(&v, i));
    }
    printf("\n");


    printf("\nAdding more elements to trigger growth...\n");
    push_back_vector(&v, 60);
    printf("Vector size: %zu, capacity: %zu\n", v.size, v.capacity);


    printf("\nDeleting element at index 2 (value: 30)...\n");
    delete_at_vector(&v, 2);

    printf("Elements after deletion: ");
    for (size_t i = 0; i < v.size; i++) {
        printf("%d ", get_at_vector(&v, i));
    }
    printf("\n");


    printf("\nCopying vector...\n");
    Vector v2 = create_vector(0, copy_int, delete_int);
    copy_vector(&v2, &v);

    printf("Original vector: ");
    for (size_t i = 0; i < v.size; i++) {
        printf("%d ", get_at_vector(&v, i));
    }
    printf("\n");

    printf("Copied vector: ");
    for (size_t i = 0; i < v2.size; i++) {
        printf("%d ", get_at_vector(&v2, i));
    }
    printf("\n");


    printf("\nAre vectors equal? %s\n", is_equal_vector(&v, &v2) ? "Yes" : "No");


    printf("\nCreating new vector copy...\n");
    Vector* v3 = copy_vector_new(&v);
    printf("New vector size: %zu\n", v3->size);


    delete_vector(&v);
    delete_vector(&v2);
    delete_vector(v3);
    if (v3)
        free(v3);

    printf("\nAll vectors cleaned up successfully!\n");

    return 0;
}
