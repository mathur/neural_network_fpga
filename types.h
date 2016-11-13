#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "formula.h"

// dynamically sized array
typedef struct {
 	uint32_t * 	array;
 	uint32_t 	used;
 	uint32_t 	size;
} array_t;

void init_array(array_t * a, uint32_t initial_size);
void insert_array(array_t * a, uint32_t element);
uint32_t get_array_value(array_t * a, uint32_t idx);
void free_array(array_t * a);
void print_array(array_t * a);

// neural network layers
typedef struct {
	float *		input_vals;
	uint32_t	curr_point;
	uint32_t	num_nodes;
	uint32_t	layer_num;
	float **	weights;
	float **	weight_deltas;
	float *		layer_net;
	float *		layer_out;
	float		bias;
} layer_2_t;

void init_layer_2(layer_2_t * l, float * input_vals, uint32_t curr_point, uint32_t num_nodes, uint32_t layer_num);
void eval_layer_2(layer_2_t * l);
void backprop_layer_2(layer_2_t * l, float other);
void free_layer_2(layer_2_t * l);

typedef struct {
	array_t	*	input_vals;
	uint32_t	curr_point;
	uint32_t	num_nodes;
	uint32_t	layer_num;
	float **	weights;
	float **	weight_deltas;
	float *		layer_net;
	float *		layer_out;
	float		bias;
} layer_1_t;

void init_layer_1(layer_1_t * l, array_t * input_vals, uint32_t curr_point, uint32_t num_nodes, uint32_t layer_num);
void eval_layer_1(layer_1_t * l);
void backprop_layer_1(layer_1_t * l, layer_2_t * other);
void free_layer_1(layer_1_t * l);

#endif // TYPES_H_