/*
	Signal Processing experiments
	Implementation of Discrete Fourier Transform
*/

#include "math.h"
#include <iostream>
using std::cout; using std::endl;

#define N 8	//Length

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
			x[n] += X[k].re * cos(2.0*M_PI/length * k * n);	 // x = complex.re * cos -
			x[n] += X[k].im * -sin(2.0*M_PI/length * k * n); //     complex.im * sin
		}
	}
	return x;
}

double* amplitudeSpectrum(complex* X, unsigned long length) {
	static double a[N];

	for (unsigned long n=0; n<N; n++) {
		a[n] = sqrt( (X[n].re * X[n].re) + (X[n].im * X[n].im) );
	}

	return a;
}

double* phaseSpectrum(complex* X, unsigned long length) {
	static double phi[N];

	for (unsigned long n=0; n<N; n++) {
		phi[n] = atan2(X[n].im, X[n].re);
	}

	return phi;
}

int main() {
	double x1[N]; 	//Test signal
	complex* X;		//Complex result of dft
	double* x2;		//Real result of idft
	double* a;		//Amplitude spectrum
	double* phi;    //Phase spectrum

	for (unsigned long n=0; n<N; n++) {
		x1[n] = 1.0*sin(2.0*M_PI/N * n) + 0.0*sin(2.0*M_PI/N * n * 3) +
				0.0*sin(2.0*M_PI/N * n * 5);
	}

	X = dft(x1, N);
	x2 = idft(X, N);
	a = amplitudeSpectrum(X, N);
	phi = phaseSpectrum(X, N);

	for (unsigned long n=0; n<N; n++) {	//Print the results
		cout.precision(3);
		cout << n << " ";
		cout << "x1 = " << std::fixed << x1[n] << ", ";
		cout << "X = (" << std::fixed << X[n].re << " " << std::fixed << X[n].im << "), ";
		cout << "x2 = " << std::fixed << x2[n] << " " << endl;
	}
	return 0;
}


/*
	q
	make
	dft -> plot.txt
	gnuplot
	plot "plot.txt" with impulses
*/
