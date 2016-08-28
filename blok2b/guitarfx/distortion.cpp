#include "distortion.hpp"

Distortion::Distortion() : Amplifier() {
    gain = 1.0;
}

void Distortion::setGain(float gain) {
    this->gain = gain;
}


void Distortion::process(float* buffer) {
    for (unsigned long n=0; n<FRAMES; n++) {
        for (int k=0; k<CHANNELS; k++) {
            buffer[n*CHANNELS+k] = tanh(buffer[n*CHANNELS+k] * gain);
        }
    }
}
