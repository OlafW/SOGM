/*
	Signal Processing experiments
	Implementation of Discrete Fourier Transform
*/

#include "math.h"
#include <iostream>
using std::cout; using std::endl;

#define N 16	//Length

typedef struct {	//Complex structure
	double re;
	double im;
} complex;

complex* dft(double* x, unsigned long length) {		//Forward DFT
	static complex X[N];	//Complex output

	for (unsigned long k=0; k<length; k++) {
		X[k].re = X[k].im = 0.0;

		for (unsigned long n=0; n<length; n++) {
			X[k].re += x[n] * cos(2.0*M_PI/length * k * n);		//Real value = x * cos
			X[k].im += x[n] * -sin(2.0*M_PI/length * k * n);	//Img value = x * -sin
		}
		X[k].re /= length;
		X[k].im /= length;
	}
	return X;
}

double* idft(complex* X, unsigned long length) {	//Inverse DFT
	static double x[N];	//Real output

	for (unsigned long n=0; n<N; n++) {
		x[n] = 0.0;

		for (unsigned long k=0; k<N; k++) {
			x[n] += X[k].re * cos(2.0*M_PI/length * k * n); 	//x = complex.re * cos -
			x[n] += X[k].im * -sin(2.0*M_PI/length * k * n);	//  	complex.im * sin
		}
	}
	return x;
}

int main() {
	double x1[N]; //Test signal
	complex* X;	//Complex result of dft
	double* x2;	//Real result of idft

	for (unsigned long n=0; n<N; n++) {
		x1[n] = sin(2.0*M_PI/N * n) + 0.33*sin(2.0*M_PI/N * 3 * n) +
						0.2*sin(2.0*M_PI/N * 5 * n);
	}

	X = dft(x1, N);
	x2 = idft(X, N);

	for (unsigned long n=0; n<N; n++) {	//Print the results
		cout.precision(3);
		cout << n << " ";
		cout << "x1 = " << std::fixed << x1[n] << ", ";
		cout << "X = (" << std::fixed << X[n].re << " " << std::fixed << X[n].im << "), ";
		cout << "x2 = " << std::fixed << x2[n] << " " << endl;
	}
	return 0;
}
