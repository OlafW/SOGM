#include "tremolo.hpp"


Tremolo::Tremolo() : Amplifier() {
    modDepth = 0.5;
    modFreq = 5;
    phase = 0;
    period = SAMPLERATE / modFreq;
}

void Tremolo::setModFreq(float modFreq) {
  this->modFreq = modFreq;
  period = SAMPLERATE / modFreq;
}

void Tremolo::setModDepth(float modDepth) {
    this->modDepth = clip(modDepth, 0.0, 1.0);
}

void Tremolo::process(float* buffer) {
  for (int n=0; n<FRAMES; n++) {
      for (int k=0; k<CHANNELS; k++) {

          float modulation = sin(phase * modFreq/SAMPLERATE * 2.0*M_PI) * 0.5 + 0.5;
          buffer[n*CHANNELS+k] = buffer[n*CHANNELS+k] * (1.0-modDepth) +
                                 buffer[n*CHANNELS+k] * modulation * modDepth;
      }
      if (++phase > period) phase = 0;
  }
}
