#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"

void init_array(array_t *a, uint32_t initial_size) {
    a->array = (uint32_t *) malloc(initial_size * sizeof(uint32_t));
    a->used = 0;
    a->size = initial_size;
}

void insert_array(array_t *a, uint32_t element) {
    if (a->used == a->size) {
        a->size *= 2;
        a->array = (uint32_t *) realloc(a->array, a->size * sizeof(uint32_t));
    }

    a->array[a->used++] = element;
}

void free_array(array_t *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

void print_array(array_t *a) {
    printf("Size of array is %d\n", a->used);
    for(int i = 0; i < a->used; i++) {
        printf("%d ", a->array[i]);
    }
    printf("\n");
}