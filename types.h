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
} int_array_t;

void init_int_array(int_array_t * a, uint32_t initial_size);
void insert_int_array(int_array_t * a, uint32_t element);
uint32_t get_int_array_value(int_array_t * a, uint32_t idx);
void free_int_array(int_array_t * a);
void print_int_array(int_array_t * a);

typedef struct {
 	float * 	array;
 	uint32_t 	used;
 	uint32_t 	size;
} float_array_t;

void init_float_array(float_array_t * a, uint32_t initial_size);
void insert_float_array(float_array_t * a, float element);
float get_float_array_value(float_array_t * a, uint32_t idx);
void free_float_array(float_array_t * a);
void print_float_array(float_array_t * a);

// neural network layers
typedef struct {
	int_array_t	*	input_vals;
	uint32_t		curr_point;
	uint32_t		num_nodes;
	uint32_t		layer_num;
	float *			weights;
	float *			weight_deltas;
	float *			layer_net;
	float *			layer_out;
	float			bias;
} layer_t;

void init_layer(layer_t * l, int_array_t * input_vals, uint32_t curr_point, uint32_t num_nodes, uint32_t layer_num);
void eval_layer(layer_t * l);
void backprop_layer_1(layer_t * l, layer_t * other);
void backprop_layer_2(layer_t * l, uint32_t val);
void free_layer(layer_t * l);

#endif // TYPES_H_