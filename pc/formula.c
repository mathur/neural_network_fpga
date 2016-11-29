#include "formula.h"

float sigmoid(float x) {
	printme(&x, sizeof(float));
    if(!ON_FPGA) {
        int sign = x > 0;
        x = fabs(x);

        float pow0 = 1;
    	float pow1 = x;
    	float pow2 = pow1 * x;

        float approx = pow0 + pow1 + pow2/2.0;

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

float inv_sigmoid(float x) {
	if(!ON_FPGA) {
		return sigmoid(x) * (1 - sigmoid(x));
	} else {
		// nothing yet
		return 0.0;
	}
}

float err(float o, float t) {
	if(!ON_FPGA) {
		return 0.5 * ((t - o) * (t - o));
	} else {
		// nothing yet
		return 0.0;
	}
}

float inv_err(float o, float t) {
	if(!ON_FPGA) {
		return (o - t);
	} else {
		// nothing yet
		return 0.0;
	}
}

static void printme(void *c, size_t n) {
	printf("%f : ", *((float *) c));
	unsigned char *t = c;
	if (c == NULL)
		return;
	while (n > 0) {
		int q;
		--n;
		for(q = 0x80; q; q >>= 1)
			printf("%x", !!(t[n] & q));
	}
	printf("\n");
}