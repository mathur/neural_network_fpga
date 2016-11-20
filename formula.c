#include "formula.h"

double sigmoid(double x) {
	if(!ON_FPGA) {
		double expr_sum = 0;
		for(int i = 0; i < 100; i++) {
			expr_sum += pow(x, i) / factorial(i);
		}

		return 1.0 / (1.0 + expr_sum);
		// return 1.0 / (1.0 + exp(-x));
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

double factorial(double n) {
	double factorial = 1;
	for(int i = 1; i <= n; ++i) {
		factorial *= i;              // factorial = factorial*i;
	}
    return factorial;
}