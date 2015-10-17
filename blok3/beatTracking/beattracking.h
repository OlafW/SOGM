#ifndef BEATTRACKING_H
#define BEATTRACKING_H

#include <iostream>
#include "math.h"
#include <vector>

using std::vector;

float* autoCorrelate(float* x, unsigned long N, int step);
float findPeriod(float* x, unsigned long N, float th);
float* normalize(float* x, unsigned long N);
float RMS(float* x, unsigned long N);

#endif
