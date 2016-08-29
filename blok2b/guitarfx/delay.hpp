#ifndef _DELAY_H_
#define _DELAY_H_

#include "amplifier.hpp"

class Delay : public Amplifier {
public:
    Delay(unsigned int ringBufferSize);
    ~Delay();
    void process(float* buffer);
    void setDelayTime(unsigned int delayTime);
    void setFeedback(float feedback);

private:
    float* ringBuffer;
    unsigned int ringBufferSize;
    unsigned int delayTime;
    float feedback;

    int readHead;
    int writeHead;
};

#endif
