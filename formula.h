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
double dot_product(double * arr1, double * arr2, double size);

#endif // FORMULA_H_