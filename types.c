#include "types.h"

// dynamically sized array
void init_array(array_t * a, float initial_size) {
    a->array = (float *) malloc(initial_size * sizeof(float));
    a->used = 0;
    a->size = initial_size;
}

void insert_array(array_t * a, float element) {
    if (a->used == a->size) {
        a->size *= 2;
        a->array = (float *) realloc(a->array, a->size * sizeof(float));
    }

    a->array[a->used++] = element;
}

float get_array_value(array_t * a, uint32_t idx) {
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
        printf("%f ", a->array[i]);
    }
    printf("\n");
}

void print_float_array(float * arr, uint32_t size) {
    for(int i = 0; i < size; i++) {
        printf("%f ", arr[i]);
    }
}

// layers
void init_layer_1(layer_1_t * l, array_t * input_vals, float curr_point, float num_nodes, float layer_num) {
    l->input_vals = input_vals;
    l->curr_point = curr_point;
    l->num_nodes = num_nodes;
    l->layer_num = layer_num;

    l->weights = (float **) malloc(num_nodes * sizeof(float *));
    for(int i = 0; i < num_nodes; i++) {
        l->weights[i] = (float *) malloc(ATTRS_PER_ENTRY * sizeof(float));
    }
    for(int i = 0; i < num_nodes; i++) {
        for(int j = 0; j < ATTRS_PER_ENTRY; j++) {
            l->weights[i][j] = drand48();
        }
    }

    l->weight_deltas = (float **) calloc(num_nodes, sizeof(float *));
    for(int i = 0; i < num_nodes; i++) {
        l->weight_deltas[i] = (float *) calloc(ATTRS_PER_ENTRY, sizeof(float));
    }

    l->layer_net = (float *) calloc(num_nodes, sizeof(float));
    l->layer_out = (float *) calloc(num_nodes, sizeof(float));
    l->bias = (drand48() * 2) - 1;
}

void eval_layer_1(layer_1_t * l) {
    float * input_vals = (float *) calloc(ATTRS_PER_ENTRY, sizeof(float));
    for(int i = 0; i < ATTRS_PER_ENTRY; i++) {
        input_vals[i] = get_array_value(l->input_vals, (l->curr_point * ATTRS_PER_ENTRY) + i);
    }

    // now calculate the dot product of input_vals and l->weights[i]
    // at each iteration
    for(int i = 0; i < l->num_nodes; i++) {
        l->layer_net[i] = dot_product(input_vals, l->weights[i], ATTRS_PER_ENTRY) + l->bias;
        l->layer_out[i] = sigmoid(l->layer_net[i]);
    }

    return;
}

void backprop_layer_1(layer_1_t * l, layer_2_t * other) {
    for(int i = 0; i < l->num_nodes; i++) {
        for(int j = 0; j < ATTRS_PER_ENTRY; j++) {
            l->weights[i][j] = l->weights[i][j] - (LEARNING_RATE * other->weight_deltas[0][i] * get_array_value(l->input_vals, j) * other->weights[0][i] * inv_sigmoid(l->layer_out[i]));
        }
    }
    return;
}

void free_layer_1(layer_1_t * l) {
    free_array(l->input_vals);

    for(int i = 0; i < l->num_nodes; i++) {
        free(l->weights[i]);
    }
    free(l->weights);
    l->weights = NULL;

    for(int i = 0; i < l->num_nodes; i++) {
        free(l->weight_deltas[i]);
    }
    free(l->weight_deltas);
    l->weight_deltas = NULL;

    free(l->layer_net);
    l->layer_net = NULL;

    free(l->layer_out);
    l->layer_out = NULL;

    l->curr_point = 0;
    l->num_nodes = 0;
    l->layer_num = 0;
    l->bias = 0;
}

void init_layer_2(layer_2_t * l, float * input_vals, float curr_point, float num_nodes, float layer_num) {
    l->input_vals = input_vals;
    l->curr_point = curr_point;
    l->num_nodes = num_nodes;
    l->layer_num = layer_num;

    l->weights = (float **) malloc(num_nodes * sizeof(float *));
    for(int i = 0; i < num_nodes; i++) {
        l->weights[i] = (float *) malloc(ATTRS_PER_ENTRY * sizeof(float));
    }
    for(int i = 0; i < num_nodes; i++) {
        for(int j = 0; j < ATTRS_PER_ENTRY; j++) {
            l->weights[i][j] = drand48();
        }
    }

    l->weight_deltas = (float **) calloc(num_nodes, sizeof(float *));
    for(int i = 0; i < num_nodes; i++) {
        l->weight_deltas[i] = (float *) calloc(ATTRS_PER_ENTRY, sizeof(float));
    }

    l->layer_net = (float *) calloc(num_nodes, sizeof(float));
    l->layer_out = (float *) calloc(num_nodes, sizeof(float));
    l->bias = (drand48() * 2) - 1;
}

void eval_layer_2(layer_2_t * l) {
    float * input_vals = (float *) calloc(ATTRS_PER_ENTRY, sizeof(float));
    for(int i = 0; i < ATTRS_PER_ENTRY; i++) {
        input_vals[i] = l->input_vals[((uint32_t) l->curr_point * ATTRS_PER_ENTRY) + i];
    }

    // now calculate the dot product of input_vals and l->weights[i]
    // at each iteration
    for(int i = 0; i < l->num_nodes; i++) {
        l->layer_net[i] = dot_product(input_vals, l->weights[i], ATTRS_PER_ENTRY) + l->bias;
        l->layer_out[i] = sigmoid(l->layer_net[i]);
    }

    return;
}

void backprop_layer_2(layer_2_t * l, float other) {
    for(int i = 0; i < l->num_nodes; i++) {
        for(int j = 0; j < ATTRS_PER_ENTRY; j++) {
            l->weight_deltas[i][j] = inv_sigmoid(l->layer_out[i]) * inv_err(l->layer_out[i], other);
            l->weights[i][j] = l->weights[i][j] - (LEARNING_RATE * l->weight_deltas[i][j] * l->input_vals[j]);
        }
    }
    return;
}

void free_layer_2(layer_2_t * l) {
    l->input_vals = NULL;

    for(int i = 0; i < l->num_nodes; i++) {
        free(l->weights[i]);
    }
    free(l->weights);
    l->weights = NULL;

    for(int i = 0; i < l->num_nodes; i++) {
        free(l->weight_deltas[i]);
    }
    free(l->weight_deltas);
    l->weight_deltas = NULL;

    free(l->layer_net);
    l->layer_net = NULL;

    free(l->layer_out);
    l->layer_out = NULL;

    l->curr_point = 0;
    l->num_nodes = 0;
    l->layer_num = 0;
    l->bias = 0;
}