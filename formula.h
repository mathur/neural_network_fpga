#ifndef FORMULA_H_
#define FORMULA_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float sigmoid(uint32_t x);
float inv_sigmoid(uint32_t x);

#endif // FORMULA_H_