#include "sinewave.h"
#include <iostream>

void SineWave::setFrequency(int frequency)  {
  this->frequency = frequency;
}


void SineWave::setAmplitude(float amplitude) {
   this->amplitude = amplitude;
}


int SineWave::setSampleRate(int sampleRate) {
  this->sampleRate = sampleRate;
  return sampleRate;
}


float SineWave::setDuration(float duration) {
  this->duration = duration;
  return duration;
}


float* SineWave::generate() {

  period = sampleRate/frequency;
  duration = sampleRate*duration;
  val = new float[int(duration)];

	for (int i=0; i<duration; i++) {
		   val[i] = sin( i* 2*M_PI / period ) * amplitude;
     }
  return val;
}
