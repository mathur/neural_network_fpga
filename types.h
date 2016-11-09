#ifndef TYPES_H_
#define TYPES_H_

typedef struct {
	uint32_t	num_nodes;
	uint32_t	input_vals;
	uint32_t	layer_num;
} layer_t;

typedef struct {
 	uint32_t 	* array;
 	uint32_t 	used;
 	uint32_t 	size;
} array_t;

void init_array(array_t *a, uint32_t initial_size);
void insert_array(array_t *a, uint32_t element);
void free_array(array_t *a);
void print_array(array_t *a);

#endif // TYPES_H_