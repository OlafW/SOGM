#ifndef _DIST_H_
#define _DIST_H_

#include "amplifier.hpp"
#include "math.h"

class Distortion : public Amplifier {

public:
    Distortion();
    void process(float* buffer);
    void setGain(float gain);

private:
    float gain;
};

#endif
