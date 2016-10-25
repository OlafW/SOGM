/*
Beat tracking algorithm
Functions:
    - autocorrelation of signal
    - extracting the average period in samples of correlated signal
    - standard deviation
    - normalizing
    - rms
*/

#ifndef BEATTRACKING_H
#define BEATTRACKING_H

#include <iostream>
#include "math.h"
#include <vector>

using std::vector;

float* autoCorrelate(float* x, unsigned long N);
float findPeriod(float* x, unsigned long N, float th_min, float th_max, float discharge);
float stdDeviation(float* x, unsigned long N);
float* normalize(float* x, unsigned long N);
float RMS(float* x, unsigned long N);

#endif
