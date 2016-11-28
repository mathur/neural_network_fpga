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

// attempts at easier sigmoids
float exp_fast_schraudolph(float a);
float factorial(float n);

#endif // FORMULA_H_