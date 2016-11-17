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