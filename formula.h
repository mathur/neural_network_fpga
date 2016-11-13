#ifndef FORMULA_H_
#define FORMULA_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "const.h"

float sigmoid(uint32_t x);
float inv_sigmoid(uint32_t x);
float err(float o, float t);
float inv_err(float o, float t);
float dot_product(float * arr1, float * arr2, uint32_t size);

#endif // FORMULA_H_