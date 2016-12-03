#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "const.h"
#include "data.h"
#include "types.h"

#define _GNU_SOURCE

int parse_training_data();
int parse_testing_data();
int main();

#endif // MAIN_H_