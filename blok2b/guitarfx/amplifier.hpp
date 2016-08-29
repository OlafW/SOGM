#ifndef _AMPLIFIER_H_
#define _AMPLIFIER_H_

#include <iostream>

const int SAMPLERATE = 44100;
const int CHANNELS = 1;
const int FRAMES = 64;

class Amplifier {

public:
    Amplifier();
    virtual ~Amplifier() {};
    virtual void process(float* buffer);
    void setGain(float gain);
    float clip(float x, float min, float max);

private:
    float gain;
};

#endif
