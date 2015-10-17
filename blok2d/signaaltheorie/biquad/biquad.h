#ifndef _BIQUAD_H
#define _BIQUAD_H

#include <iostream>
#include "math.h"
using namespace std;

class Biquad {
public:
	Biquad(double coeffs[]);
	double process(float x);

private:
	double y[2];	//Memory y
	double x[2];	//Memory x
	double a0,a1,a2,b1,b2;	//Coefficients
};

#endif
