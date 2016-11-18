#include "main.h"

// each row has 1 target + 100 attributes
array_t 	target_vals;
array_t 	attr_vals;

// layers
layer_1_t	layer_1;
layer_2_t	layer_2;

uint32_t	curr_point;
uint32_t 	total_runs;
uint32_t	num_incorrect;
double		prev_sample_err;
double		curr_sample_err;

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
	printf("Initializing neural network...\n");
	srand48(time(NULL));

	init_array(&target_vals, INITIAL_ARR_SIZE);
	init_array(&attr_vals, INITIAL_ARR_SIZE);

	init_layer_1(&layer_1, &attr_vals, curr_point, LAYER_1_NUM_NODES, 1);
	init_layer_2(&layer_2, layer_1.layer_out, curr_point, 1, 2, LAYER_1_NUM_NODES);

	printf("Parsing training dataset...\n");
	if(parse_data("mushroom-training.txt") == -1) {
		printf("Failed to parse dataset\n");
		return -1;
	}

	printf("Starting training...\n");
	double total_err = 0;
	while(1) {
		// set up the first layer and evaluate it
		layer_1.curr_point = curr_point;
		eval_layer_1(&layer_1);

		// set up the second layer and evaluate it
		layer_2.curr_point = curr_point;
		eval_layer_2(&layer_2);

		backprop_layer_2(&layer_2, get_array_value(&target_vals, curr_point));
		backprop_layer_1(&layer_1, &layer_2);

		double curr_err = err(layer_2.layer_out[0], get_array_value(&target_vals, curr_point));
		total_err += curr_err;
		if(total_runs % ITER_TO_CHECK == 0) {
			if((total_err / ITER_TO_CHECK) < CONVERGENCE_THRESHOLD) {
				printf("Data has converged at the %dth run\n", total_runs);
				break;
			}
			total_err = 0;
		}
		printf("Current iteration: %d\n", total_runs);
		printf("Current error: %f\n\n", curr_err);

		// move onto the next data entry
		total_runs++;
		curr_point++;
		if(curr_point >= target_vals.used) {
			curr_point = 0;
		}
	}

	printf("Done training! Press ENTER to begin testing the neural network.\n");
	getchar();

	// clean up arrays from training
	free_array(&target_vals);
	free_array(&attr_vals);
	printf("Parsing training dataset...\n");
	if(parse_data("mushroom-testing.txt") == -1) {
		printf("Failed to parse dataset\n");
		return -1;
	}

	// test here
	printf("Starting testing...\n");
	while(curr_point < target_vals.used) {
		// set up the first layer and evaluate it
		layer_1.curr_point = curr_point;
		eval_layer_1(&layer_1);

		// set up the second layer and evaluate it
		layer_2.curr_point = curr_point;
		eval_layer_2(&layer_2);

		// round up or down
		double temp = 0;
		if(layer_2.layer_out[0] >= 0.5) {
			temp = 1;
		}

		// check for validity of input
		if(temp != get_array_value(&target_vals, curr_point)) {
			num_incorrect++;
		}

		// move onto the next data entry
		total_runs++;
		curr_point++;
	}

	printf("Incorrectly classified from testing dataset: %d\n", num_incorrect);
	printf("Accuracy percentage: %0.2f%%\n", (1 - ((double) num_incorrect) / target_vals.used) * 100);
	getchar();

	free_layer_1(&layer_1);
	free_layer_2(&layer_2);
	free_array(&target_vals);
	free_array(&attr_vals);

	return 0;
}