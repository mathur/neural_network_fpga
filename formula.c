#include "formula.h"

double sigmoid(double x) {
	if(!ON_FPGA) {
		return 1.0 / (1.0 + exp(-x));
	} else {
		// nothing yet
		return 0.0;
	}
}

double inv_sigmoid(double x) {
	if(!ON_FPGA) {
		return sigmoid(x) * (1 - sigmoid(x));
	} else {
		// nothing yet
		return 0.0;
	}
}

double err(double o, double t) {
	if(!ON_FPGA) {
		return 0.5 * ((t - o) * (t - o));
	} else {
		// nothing yet
		return 0.0;
	}
}

double inv_err(double o, double t) {
	if(!ON_FPGA) {
		return (o - t);
	} else {
		// nothing yet
		return 0.0;
	}
}

double dot_product(double * arr1, double * arr2, double size) {
	double total_sum = 0;
	for(int i = 0; i < size; i++) {
		total_sum += (arr1[i] * arr2[i]);
	}
	return total_sum;
}