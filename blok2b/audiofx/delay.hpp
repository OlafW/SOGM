#ifndef _DELAY_H_
#define _DELAY_H_

#include "amplifier.hpp"

class Delay : public Amplifier {
public:
    Delay(int maxDelayTime);
    ~Delay();
    void process(float* buffer);
    void setDelayTimeMs(int delayTime);
    void setFeedback(float feedback);
    void setMix(float mix);

private:
    float* ringBuffer;
    unsigned int ringBufferSize;
    unsigned int readHead;
    unsigned int writeHead;

    unsigned int delayTime;
    float feedback;
    float mix;
};

#endif
