#include "STFT.hpp"

STFT::STFT() {
    N = CHANNELS * FRAMES;
    M = WINDOWSIZE;
    bins = HOPSIZE;
    H = FFTSIZE;

    window = blackMan(M);
}

STFT::~STFT() {
    delete[] window;
}

void STFT::fft(float* data, unsigned long nn) {
    unsigned long n, mmax, m, j, istep, i;
    float wtemp, wr, wpr, wpi, wi, theta;
    float tempr, tempi;

    // reverse-binary reindexing
    n = nn << 1;
    j = 1;
    for (i = 1; i < n; i += 2) {
        if (j > i) {
            std::swap(data[j-1], data[i-1]);
            std::swap(data[j], data[i]);
        }
        m = nn;
        while (m >= 2 && j > m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    };

    // Danielson-Lanczos
    mmax = 2;
    while (n > mmax) {
        istep = mmax << 1;
        theta = -(2 * M_PI / mmax);
        wtemp = sin(0.5 * theta);
        wpr = -2.0 * wtemp*wtemp;
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        for (m = 1; m < mmax; m += 2) {
            for (i = m; i <= n; i += istep) {
                j= i + mmax;
                tempr = wr * data[j-1] - wi * data[j];
                tempi = wr * data[j] + wi * data[j-1];

                data[j-1] = data[i-1] - tempr;
                data[j] = data[i] - tempi;
                data[i-1] += tempr;
                data[i] += tempi;
            }
            wtemp = wr;
            wr += wr*wpr - wi*wpi;
            wi += wi*wpr + wtemp*wpi;
        }
        mmax = istep;
    }
}

float* STFT::blackMan(unsigned long M) {
    float a0, a1, a2;
    a0 = 7938.0/18608.0;
    a1 = 9240.0/18608.0;
    a2 = 1430.0/18608.0;

    float* w = new float[M];
    for (unsigned long n=0; n<M; ++n) {
        w[n] = a0 - a1 * cos((TWOPI * (long double)n) / ((long double)M - 1)) +
                    a2 * cos((TWOPI*2.0 * (long double)n) / ((long double)M - 1));
    }
    return w;
}

float* STFT::zeroPad(float* x, unsigned long N, unsigned long newN) {
    float* y = new float[newN];

    for (unsigned long n=0; n<N; ++n)
        y[n] = x[n];
    for (unsigned long n=N; n<newN; ++n)
        y[n] = 0;

    return y;
}

// float** STFT::stft(float *) {
//
// }
