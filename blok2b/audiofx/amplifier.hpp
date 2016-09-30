#ifndef _AMPLIFIER_H_
#define _AMPLIFIER_H_

#include <iostream>
#include "audioFxConstants.hpp"

class Amplifier {

public:
    Amplifier();
    virtual ~Amplifier() {};
    virtual void process(float* buffer);
    
    void setGain(float gain);
    float clip(float x, float min, float max);

protected:
    float gain;
};

#endif
