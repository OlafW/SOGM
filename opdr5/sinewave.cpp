#include "sinewave.h"
#include <iostream>

void SineWave::setFrequency(int new_freq)  {
  frequency = new_freq;
}


void SineWave::setAmplitude(float new_amp) {
  amplitude = new_amp;
}


void SineWave::setSampleRate(int new_samplerate) {
  sampleRate = new_samplerate;
}


void SineWave::setDuration(float new_dur) {
  duration = new_dur;
}


void SineWave::generate() {
  period = sampleRate/frequency;
  duration = sampleRate*duration;

	 for (int i=0; i<duration; i++) {
		   val = sin(i* 2*M_PI / period ) * amplitude;
       cout << val << endl;
     }
}
