/*
	Signal Processing experiments
	Implementation of Discrete Fourier Transform with complex c++ libary
*/

#include <complex>
#include <iostream>

using std::complex;
using std::cout; using std::endl;

const int N = 1024;                 // Size of transform
const complex<double> I (0.0, 1.0); // Imaginary number

complex<double>* DFT(complex<double>* x) {
    static complex<double> X[N];

    for (unsigned long k=0; k<N; k++) {
        X[k] = 0.0;
        for (unsigned long n=0; n<N; n++) {
            // X[k] = 1/N ∑ x[n] * e^-i2πk n/N
            X[k] += x[n] * exp(2.0*M_PI * -I / double(N) * double(n * k));
        }
        X[k] /= N;
    }

    return X;
}

complex<double>* IDFT(complex<double>* X) {
    static complex<double> x[N];

    for (unsigned long n=0; n<N; n++) {
        x[n] = 0.0;
        for (unsigned long k=0; k<N; k++) {
            // x[n] = ∑ X[k] * e^i2πk n/N
            x[n] += X[k] * exp(2.0*M_PI * I / double(N) * double(n * k));
        }
    }

    return x;
}

double* amplitudeSpectrum(complex<double>* X) {
    static double amp[N];

    for (unsigned long n=0; n<N; n++) {
        amp[n] = abs(X[n]);
    }
    return amp;
}

double* phaseSpectrum(complex<double>* X) {
    static double phase[N];

    for (unsigned long n=0; n<N; n++) {
        phase[n] = arg(X[n]);
    }
    return phase;
}

double* hammingWindow() {
    static double y[N];
    double a = 0.54; // Hamming: a = 0.54, Hanning: a = 0.5;

    for (int n=0; n<N; n++) {
        y[n] = (1.0 - a) * cos(2.0*M_PI / N * n + M_PI) + a;
    }
    return y;
}

int main() {
    complex<double> x1[N];  // Zero padded real signal
    complex<double>* X;     // Complex result of dft of x1
    complex<double>* x2;    // Complex result of idft of X
    double* hamm;           // Hamming window
    double* amp;            // Amplitude spectrum
    double* phase;          // Phase spectrum

    // Test signal is sine with period of N
    // Apply hamming window to signal
    hamm = hammingWindow();
    for (unsigned long n=0; n<N; n++) {
        x1[n] = sin(2.0*M_PI / N * n) * hamm[n];
    }

    X = DFT(x1);
    x2 = IDFT(X);
    // Divide IDFT result by hamming window
    for (int n=0; n<N; n++) {
        x2[n] /= hamm[n];
    }
    amp = amplitudeSpectrum(X);
    phase = phaseSpectrum(X);

    for (unsigned long n=0; n<N; n++) {
        cout.precision(3);
        cout << std::fixed << x2[n].real() << endl;
    }

    return 0;
}

/*
	q
	make
	dft_complex -> plot.txt
	gnuplot
	plot "plot.txt" with lines
*/
