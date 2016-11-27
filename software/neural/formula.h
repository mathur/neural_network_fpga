#ifndef FORMULA_H_
#define FORMULA_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "const.h"

double sigmoid(double x);
double inv_sigmoid(double x);
double err(double o, double t);
double inv_err(double o, double t);

// attempts at easier sigmoids
double exp_fast_schraudolph(double a);
double factorial(double n);

#endif // FORMULA_H_