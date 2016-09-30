#ifndef _STFT_HPP_
#define _STFT_HPP_

#include <iostream>
#include <cmath>
#include "audioFxConstants.hpp"

class STFT {
public:
    STFT();
    ~STFT();

    void fft(float* data, unsigned long nn);
    float** stft(float* x);

    float* blackMan(unsigned long M);
    float* zeroPad(float* x, unsigned long N, unsigned long newN);

private:
    unsigned long N;
    unsigned long M;
    unsigned long bins;
    unsigned long H;

    float* window;
};

#endif
