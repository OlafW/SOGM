#include "sinewave.h"
#include <iostream>

void SineWave::setFrequency(int new_freq)  {
  frequency = new_freq;
}


void SineWave::setAmplitude(float new_amp) {
  amplitude = new_amp;
}


int SineWave::setSampleRate(int new_samplerate) {
  sampleRate = new_samplerate;
  return sampleRate;
}


float SineWave::setDuration(float new_dur) {
  duration = new_dur;
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
  delete[] val;
}
