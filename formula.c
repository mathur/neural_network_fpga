#include "formula.h"

double sigmoid(double x) {
    if(!ON_FPGA) {
        // return 1. / (1. + exp(-x));
    	// return (atan(x) + 1) / 2;
        // return (0.5) * ( ( x / (1 + fabs(x)) ) + 1);
        // return (0.5) * ( cbrt( x / (1 + fabs(x)) ) + 1);
        int sign = x > 0;
        x = fabs(x);

        double pow0 = 1;
    	double pow1 = x;
    	double pow2 = pow1*x;
    	double pow3 = pow2*x;
    	double pow4 = pow3*x;

        double approx = pow0 +
        				pow1 +
        				pow2/2.;/* +
                        pow3/6. +
                        pow4/24.;*/

        if (sign) {
        	return approx / (1.0 + approx);
        } else {
        	return 1.0 / (1.0 + approx);
        }
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