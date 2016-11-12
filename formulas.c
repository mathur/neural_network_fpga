#include "formulas.h"

float sigmoid(uint32_t x) {
	if(!ON_FPGA) {
		return 1.0 / (1.0 + exp(-x));
	}

	return 0.0;
}

float inv_sigmoid(uint32_t x) {
	if(!ON_FPGA) {
		return sigmoid(x) * (1 - sigmoid(x));
	}

	return 0.0;
}

float err(float o, float t) {
	if(!ON_FPGA) {
		float mid_result = t - o;
		return 0.5 * (mid_result * mid_result);
	}

	return 0.0;
}

float inv_err(float o, float t) {
	if(!ON_FPGA) {
		return (o - t);
	}

	return 0.0;
}