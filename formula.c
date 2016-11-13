#include "formula.h"

float sigmoid(uint32_t x) {
	if(!ON_FPGA) {
		return 1.0 / (1.0 + exp(-x));
	} else {
		// nothing yet
	}

	return 0.0;
}

float inv_sigmoid(uint32_t x) {
	if(!ON_FPGA) {
		return sigmoid(x) * (1 - sigmoid(x));
	} else {
		// nothing yet
	}

	return 0.0;
}

float err(float o, float t) {
	if(!ON_FPGA) {
		float mid_result = t - o;
		return 0.5 * (mid_result * mid_result);
	} else {
		// nothing yet
	}

	return 0.0;
}

float inv_err(float o, float t) {
	if(!ON_FPGA) {
		return (o - t);
	} else {
		// nothing yet
	}

	return 0.0;
}

float dot_product(float * arr1, float * arr2, uint32_t size) {
	float total_sum = 0;
	for(int i = 0; i < size; i++) {
		total_sum += (arr1[i] * arr2[i]);
	}
	return total_sum;
}