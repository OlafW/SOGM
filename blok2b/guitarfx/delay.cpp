#include "delay.hpp"

Delay::Delay(unsigned int ringBufferSize) : Amplifier() {
    this->ringBufferSize = (ringBufferSize * SAMPLERATE) / 1000;
    delayTime = this->ringBufferSize*CHANNELS;
    feedback = 0.0;
    readHead = 0;
    writeHead = delayTime-FRAMES*CHANNELS;

    ringBuffer = new float[this->ringBufferSize*CHANNELS];

    for (int n=0; n<this->ringBufferSize; n++)
        for (int k=0; k<CHANNELS; k++) ringBuffer[n*CHANNELS+k] = 0.0;
}

Delay::~Delay() {
    delete[] ringBuffer;
}

void Delay::process(float* buffer) {
    // Write to ringbuffer
    for (int n=0; n<FRAMES; n++) {
        for (int k=0; k<CHANNELS; k++) {
            ringBuffer[writeHead] = buffer[n*CHANNELS+k];
            writeHead = (writeHead+1) % ringBufferSize;
         }
    }

    // Read from ringbuffer
    for (int n=0; n<FRAMES; n++) {
        for (int k=0; k<CHANNELS; k++) {
            buffer[n*CHANNELS+k] = ringBuffer[readHead];
            readHead = (readHead+1) % ringBufferSize;
        }
    }

    // for (int i=0; i<ringBufferSize; i++)
    //     std::cout << ringBuffer[i] << " ";
    // std::cout << "\n";
    //
    // for (int i=0; i<FRAMES*CHANNELS; i++)
    //     std::cout << buffer[i] << " ";
    // std::cout << "\n";
}

void Delay::setDelayTime(unsigned int delayTime) {
    this-> delayTime = (delayTime * SAMPLERATE) / 1000 * CHANNELS;
    this->delayTime = clip(this->delayTime, FRAMES, ringBufferSize*CHANNELS);
    writeHead = this->delayTime-FRAMES*CHANNELS;
}

void Delay::setFeedback(float feedback) {
    this->feedback = clip(feedback, 0.0, 1.0);
}
