#include "formula.h"

volatile float *to_sig_hw_port = (float *) 0x00000070;
volatile float *to_sig_sw_port = (float *) 0x00000090;

volatile float *to_isig_hw_port = (float *) 0x000000c0;
volatile float *to_isig_sw_port = (float *) 0x000000d0;

float sigmoid(float x) {
	// calcualte the taylor series expansion of e^x, and then use it in sigmoid
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
    	*to_sig_hw_port = x;
    	return *to_sig_sw_port;
    }
}

float inv_sigmoid(float x) {
	if(!ON_FPGA) {
		return sigmoid(x) * (1 - sigmoid(x));
	} else {
		*to_isig_hw_port = x;
		return *to_isig_sw_port;
	}
}

float err(float o, float t) {
	// calculate the error of our output vs our target
	return 0.5 * ((t - o) * (t - o));
}

float inv_err(float o, float t) {
	return (o - t);
}

void debug(float x) {
	printf("Floating Point:\n");
	printf("%f : ", x);
	printme(&x, sizeof(float));

	printf("Fixed Point:\n");
	// convert to fixed point
	printf("\n");
}

static void printme(void *c, size_t n) {
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
