#include "biquad.hpp"

Biquad::Biquad(int mode, float freq, float Q, float gain) {
    this->mode = mode;
    this->freq = freq;
    this->Q = Q;
    this->gain = gain;
    calculateCoefficients(mode, freq, Q, gain);
}

void Biquad::process(float* buffer) {
    for (int n=0; n<FRAMES; n++) {
        for (int k=0; k<CHANNELS; k++) {

            float _y = a0*buffer[n*CHANNELS+k] + a1*x[0] + a2*x[1] - b1*y[0] - b2*y[1];
            x[1] = x[0];
            x[0] = buffer[n*CHANNELS+k];

            y[1] = y[0];
            y[0] = _y;
            buffer[n*CHANNELS+k] = _y;
        }
    }
}

void Biquad::calculateCoefficients(int mode, float freq, float Q, float gain) {
    float norm;

    float V = pow(10, fabs(gain) / 20);
    float K = tan(M_PI * SAMPLERATE / freq);

    switch (mode) {
        case LOWPASS:
            norm = 1.0 / (1.0 / K / Q + K * K);
            a0 = K * K * norm;
            a1 = 2 * a0;
            a2 = a0;
            b1 = 2 * (K * K - 1) * norm;
            b2 = (1 - K / Q + K * K) * norm;
            break;
            
        case HIGHPASS:
            break;
    }
}

void Biquad::setMode(int mode) {
    this->mode = mode;
    calculateCoefficients(mode, freq, Q, gain);
}

void Biquad::setFrequency(float freq) {
    this->freq = freq;
    calculateCoefficients(mode, freq, Q, gain);
}

void Biquad::setQ(float Q) {
    this->Q = Q;
    calculateCoefficients(mode, freq, Q, gain);
}
