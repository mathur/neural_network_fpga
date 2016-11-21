#include "formula.h"

double sigmoid(double x) {
    if(!ON_FPGA) {
        // return (atan(x) + 1) / 2;
        double approx = 1 + x + pow(x,2)/factorial(2)
                              + pow(x,3)/factorial(3)
                              + pow(x,4)/factorial(4)
                              + pow(x,5)/factorial(5)
                              + pow(x,6)/factorial(6);
        if (x > 0) {
            approx = pow(approx, -1);
        }
        return 1.0 / (1.0 + approx);
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

/* Schraudolph's published algorithm */
double exp_fast_schraudolph(double a) {
  union { double d; int x[2]; } u;
  u.x[1] = (int) (1512775 * a + 1072632447);
  u.x[0] = 0;
  return u.d;
}

double factorial(double n) {
	double factorial = 1;
	for(int i = 1; i <= n; ++i) {
		factorial *= i;              // factorial = factorial*i;
	}
    return factorial;
}