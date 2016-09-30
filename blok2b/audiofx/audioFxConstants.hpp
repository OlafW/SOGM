#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

#include <iostream>
#include <math.h>

const int SAMPLERATE = 44100;
const int CHANNELS = 1;
const int FRAMES = 512;

const int FFTSIZE = (FRAMES * CHANNELS) / 2;
const int WINDOWSIZE = FFTSIZE;
const int HOPSIZE = 128;

const double TWOPI = M_PI+M_PI;

#endif
