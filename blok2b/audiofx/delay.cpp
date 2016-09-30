#include "delay.hpp"

Delay::Delay(int maxDelayTime) : Amplifier() {
    ringBufferSize = (maxDelayTime * SAMPLERATE) / 1000;

    delayTime = ringBufferSize * CHANNELS;
    writeHead = delayTime - FRAMES*CHANNELS;
    readHead = 0;
    feedback = 0.0;
    mix = 1.0;

    ringBuffer = new float[ringBufferSize*CHANNELS];
    for (int n=0; n<ringBufferSize; n++)
        for (int k=0; k<CHANNELS; k++) ringBuffer[n*CHANNELS+k] = 0.0;
}

Delay::~Delay() {
    delete[] ringBuffer;
}

void Delay::process(float* buffer) {
    for (int n=0; n<FRAMES; n++) {
        for (int k=0; k<CHANNELS; k++) {
            // Write to ringbuffer
            ringBuffer[writeHead] = ringBuffer[writeHead]*feedback + buffer[n*CHANNELS+k];
            writeHead = (writeHead+1) % delayTime;

            // Read from ringbuffer
            buffer[n*CHANNELS+k] = buffer[n*CHANNELS+k] * (1.0-mix) + ringBuffer[readHead] * mix;
            readHead = (readHead+1) % delayTime;
         }
    }
}

void Delay::setDelayTimeMs(int delayTime) {
    this->delayTime = (delayTime * SAMPLERATE) / 1000 * CHANNELS;
    this->delayTime = clip(this->delayTime, FRAMES*CHANNELS, ringBufferSize*CHANNELS);

    writeHead = this->delayTime-FRAMES*CHANNELS;
}

void Delay::setFeedback(float feedback) {
    this->feedback = clip(feedback, 0.0, 1.0);
}

void Delay::setMix(float mix) {
    this->mix = clip(mix, 0.0, 1.0);
}
