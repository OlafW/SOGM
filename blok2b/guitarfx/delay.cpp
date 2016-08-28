#include "delay.hpp"

Delay::Delay(unsigned int maxDelayTime) : Amplifier() {
    this->maxDelayTime = (maxDelayTime * SAMPLERATE) / 1000;

    delayTime = maxDelayTime;
    readHead = 0;
    writeHead = 0;
    feedback = 0.0;

    ringBuffer = new float[maxDelayTime];
    for (unsigned int n=0; n<maxDelayTime; n++) {
        ringBuffer[n] = 0.0;
    }
}

Delay::~Delay() {
    delete[] ringBuffer;
}

void Delay::process(float* buffer) {
    for (unsigned long n=0; n<FRAMES; n++) {
        for (int k=0; k<CHANNELS; k++) {
            ringBuffer[(delayTime-1)-writeHead] = buffer[(FRAMES*CHANNELS-1) - (n*CHANNELS+k)];
            std::cout << (delayTime-1)-writeHead << " " << (FRAMES*CHANNELS-1) - (n*CHANNELS+k) << std::endl;
            writeHead = (writeHead+1) % delayTime;
        }
    }

    for (unsigned long n=0; n<FRAMES; n++) {
        for (int k=0; k<CHANNELS; k++) {
            buffer[n*CHANNELS+k] = ringBuffer[readHead];
            readHead = (readHead+1) % delayTime;
        }
    }
}


void Delay::setDelayTime(unsigned int delayTime) {
    this->delayTime = (delayTime * SAMPLERATE) / 1000;
}
