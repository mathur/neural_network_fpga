#include "main.h"

// each row has 1 target + 100 attributes
array_t 	target_vals;
array_t 	attr_vals;

layer_t		layer_1;
layer_t		layer_2;

uint32_t 	curr_point 		= 0;
uint32_t 	total_runs 		= 0;
uint32_t	num_incorrect 	= 0;
uint32_t 	prev_sample_err = 0;
uint32_t	curr_sample_err = 0;

int parse_data(char * fname) {
	// reset dataset
	init_array(&target_vals, INITIAL_ARR_SIZE);
	init_array(&attr_vals, INITIAL_ARR_SIZE);
	curr_point 		= 0;
	total_runs 		= 0;
	num_incorrect 	= 0;
	prev_sample_err = 0;
	curr_sample_err = 0;

	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen(fname, "r");
	if (fp == NULL)
	    return -1;

	while ((read = getline(&line, &len, fp)) != -1) {
		// trim newline character at the end of the line
		size_t ln = strlen(line) - 1;
		if (*line && line[ln] == '\n') {
		    line[ln] = '\0';
		}

		uint8_t first_elem = 1;
	    // split by delimiter
		char *token;
		while ((token = strsep(&line, ","))) {
			if(first_elem) {
				insert_array(&target_vals, atoi(token));
				first_elem = 0;
			} else {
				insert_array(&attr_vals, atoi(token));
			}
		}
	}

	fclose(fp);

	if (line) {
	    free(line);
	}

	return 0;
}

int main() {
	printf("Parsing training dataset...\n");
	if(parse_data("mushroom-training.txt") == -1) {
		return -1;
	}

	printf("Initializing neural network...\n");
	srand48(time(NULL));

	init_layer(&layer_1, &attr_vals, curr_point, 6, 1);
	//init_layer(&layer_2, layer_1->layer_out, 1, 2);

	while(total_runs < NUM_TRAINING_ITERATIONS) {
		total_runs++;
		curr_point++;
		if(curr_point >= target_vals.used) {
			curr_point = 0;
		}
	}

	printf("Cleaning up...\n");
	free_array(&target_vals);
	free_array(&attr_vals);

	return 0;
}