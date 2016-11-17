#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "formula.h"

// dynamically sized array
typedef struct {
 	double * 	array;
 	uint32_t 	used;
 	double 		size;
} array_t;

void init_array(array_t * a, double initial_size);
void insert_array(array_t * a, double element);
double get_array_value(array_t * a, uint32_t idx);
void free_array(array_t * a);
void print_array(array_t * a);

double dot_product_1(array_t * arr1, double * arr2, double size, uint32_t curr_point);
double dot_product_2(double * arr1, double * arr2, double size);

// neural network layers
typedef struct {
	double *	input_vals;
	double		curr_point;
	double		num_nodes;
	double		layer_num;
	double		input_num_nodes;
	double **	weights;
	double **	weight_deltas;
	double *	layer_net;
	double *	layer_out;
	double		bias;
} layer_2_t;

void init_layer_2(layer_2_t * l, double * input_vals, double curr_point, double num_nodes, double layer_num, double input_num_nodes);
void eval_layer_2(layer_2_t * l);
void backprop_layer_2(layer_2_t * l, double other);
void free_layer_2(layer_2_t * l);

typedef struct {
	array_t	*	input_vals;
	double		curr_point;
	double		num_nodes;
	double		layer_num;
	double **	weights;
	double **	weight_deltas;
	double *	layer_net;
	double *	layer_out;
	double		bias;
} layer_1_t;

void init_layer_1(layer_1_t * l, array_t * input_vals, double curr_point, double num_nodes, double layer_num);
void eval_layer_1(layer_1_t * l);
void backprop_layer_1(layer_1_t * l, layer_2_t * other);
void free_layer_1(layer_1_t * l);

#endif // TYPES_H_