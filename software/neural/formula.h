#ifndef FORMULA_H_
#define FORMULA_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "const.h"

float sigmoid(float x);
float inv_sigmoid(float x);
float err(float o, float t);
float inv_err(float o, float t);

void debug(float x);
static void printme(void *c, size_t n);

#endif // FORMULA_H_
