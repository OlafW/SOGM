#include "biquad.h"

Biquad::Biquad(double coeffs[]) {
	a0 = coeffs[0];
	a1 = coeffs[1];
	a2 = coeffs[2];
	b1 = coeffs[3];
	b2 = coeffs[4];

	for (int i=0; i<2 ; i++) {
		x[i] = 0;
		y[i] = 0;
	}
}

double Biquad::process(float sig) {

	float res = a0*sig + a1*x[0] + a2*x[1] - b1*y[0] - b2*y[1];

	x[1] = x[0];
	x[0] = sig;

	y[1] = y[0];
	y[0] = res;

	return res;
}
