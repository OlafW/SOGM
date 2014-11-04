#ifndef _SINE_H_
#define _SINE_H_

#include <string>
#include <math.h>
using namespace std;


class SineWave {

public:
    void setFrequency(int frequency);
    void setAmplitude(float amplitude);
    int setSampleRate(int sampleRate=44100);
    float setDuration(float duration);
    float* generate();

private:
  int sampleRate;
  int frequency;
  float amplitude;
  float duration;
  float period;
  float* val;

};

#endif
