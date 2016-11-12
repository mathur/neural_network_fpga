#include "types.h"

// dynamically sized array
void init_array(array_t * a, uint32_t initial_size) {
    a->array = (uint32_t *) malloc(initial_size * sizeof(uint32_t));
    a->used = 0;
    a->size = initial_size;
}

void insert_array(array_t * a, uint32_t element) {
    if (a->used == a->size) {
        a->size *= 2;
        a->array = (uint32_t *) realloc(a->array, a->size * sizeof(uint32_t));
    }

    a->array[a->used++] = element;
}

uint32_t get_array_value(array_t * a, uint32_t idx) {
    if(idx >= a->used) {
        return -1;
    } else {
        return a->array[idx];
    }
}

void free_array(array_t *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

void print_array(array_t * a) {
    printf("Size of array is %d\n", a->used);
    for(int i = 0; i < a->used; i++) {
        printf("%d ", a->array[i]);
    }
    printf("\n");
}

// layers
void init_layer(layer_t * l, array_t * input_vals, uint32_t curr_point, uint32_t num_nodes, uint32_t layer_num) {
    l->input_vals = input_vals;
    l->curr_point = curr_point;
    l->num_nodes = num_nodes;
    l->layer_num = layer_num;
    l->weights = (float *) malloc(ATTRS_PER_ENTRY * num_nodes * sizeof(float));
    for(int i = 0; i < (ATTRS_PER_ENTRY * num_nodes); i++) {
        l->weights[i] = drand48();
    }
    l->weight_deltas = (float *) calloc(ATTRS_PER_ENTRY * num_nodes, sizeof(float));
    l->layer_net = (float *) calloc(num_nodes, sizeof(float));
    l->layer_out = (float *) calloc(num_nodes, sizeof(float));
    l->bias = (drand48() * 2) - 1;
}

void eval_layer(layer_t * l) {
    // TODO implement this
    return;
}

void backprop_layer_1(layer_t * l, layer_t * other) {
    // TODO implement this
    return;
}

void backprop_layer_2(layer_t * l, uint32_t val) {
    // TODO implement this
    return;
}

void free_layer(layer_t * l) {
    free_array(l->input_vals);

    l->curr_point = 0;
    l->num_nodes = 0;
    l->layer_num = 0;

    free(l->weights);
    l->weights = NULL;

    free(l->weight_deltas);
    l->weight_deltas = NULL;

    free(l->layer_net);
    l->layer_net = NULL;

    free(l->layer_out);
    l->layer_out = NULL;

    l->bias = 0;
}