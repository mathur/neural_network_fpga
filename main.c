#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "types.h"

array_t target_vals;
array_t attr_vals;

int parse_data(char * fname) {
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

	if (line)
	    free(line);

	return 0;
}

int main() {
	printf("Initializing neural network...\n");
	init_array(&target_vals, INITIAL_ARR_SIZE);
	init_array(&attr_vals, INITIAL_ARR_SIZE);

	printf("Parsing training dataset...\n");
	if(-1 == parse_data("mushroom-training.txt")) {
		exit(EXIT_FAILURE);
	}

	printf("Cleaning up...\n");
	free_array(&target_vals);
	free_array(&attr_vals);

    return 0;
}