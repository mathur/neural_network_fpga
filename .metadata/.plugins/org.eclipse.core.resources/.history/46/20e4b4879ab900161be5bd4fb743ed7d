#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "formula.h"

// dynamically sized array
typedef struct {
 	float * 	array;
 	uint32_t 	used;
 	float 		size;
} array_t;

void init_array(array_t * a, float initial_size);
void insert_array(array_t * a, float element);
float get_array_value(array_t * a, uint32_t idx);
void free_array(array_t * a);
void print_array(array_t * a);

float dot_product_1(array_t * arr1, float * arr2, float size, uint32_t curr_point);
float dot_product_2(float * arr1, float * arr2, float size);

// neural network layers
typedef struct {
	float *	input_vals;
	float		curr_point;
	float		num_nodes;
	float		layer_num;
	float		input_num_nodes;
	float **	weights;
	float **	weight_deltas;
	float *	layer_net;
	float *	layer_out;
	float		bias;
} layer_2_t;

void init_layer_2(layer_2_t * l, float * input_vals, float curr_point, float num_nodes, float layer_num, float input_num_nodes);
void eval_layer_2(layer_2_t * l);
void backprop_layer_2(layer_2_t * l, float other);
void free_layer_2(layer_2_t * l);

typedef struct {
	array_t	*	input_vals;
	float		curr_point;
	float		num_nodes;
	float		layer_num;
	float **	weights;
	float **	weight_deltas;
	float *	layer_net;
	float *	layer_out;
	float		bias;
} layer_1_t;

void init_layer_1(layer_1_t * l, array_t * input_vals, float curr_point, float num_nodes, float layer_num);
void eval_layer_1(layer_1_t * l);
void backprop_layer_1(layer_1_t * l, layer_2_t * other);
void free_layer_1(layer_1_t * l);

#endif // TYPES_H_