#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "const.h"

// dynamically sized array
typedef struct {
 	uint32_t * 	array;
 	uint32_t 	used;
 	uint32_t 	size;
} array_t;

void init_array(array_t *a, uint32_t initial_size);
void insert_array(array_t *a, uint32_t element);
void free_array(array_t *a);
void print_array(array_t *a);

// neural network layers
typedef struct {
	array_t	*	input_vals;
	uint32_t	curr_point;
	uint32_t	num_nodes;
	uint32_t	layer_num;
	float *		weights;
	float *		weight_deltas;
	float *		layer_net;
	float *		layer_out;
	float		bias;
} layer_t;

void init_layer(layer_t * l, array_t * input_vals, uint32_t curr_point, uint32_t num_nodes, uint32_t layer_num);
void eval_layer(layer_t * l);
void free_layer(layer_t * l);

#endif // TYPES_H_