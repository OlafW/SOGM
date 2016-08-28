#ifndef _DELAY_H_
#define _DELAY_H_

#include "amplifier.hpp"

class Delay : public Amplifier {
public:
    Delay(unsigned int maxDelayTime);
    ~Delay();
    void process(float* buffer);
    void setDelayTime(unsigned int delayTime);

private:
    double* ringBuffer;

    unsigned int readHead;
    unsigned int writeHead;
    unsigned int delayTime;
    unsigned int maxDelayTime;
    float feedback;
};

#endif
