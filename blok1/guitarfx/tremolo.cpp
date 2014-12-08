#include "tremolo.h"
#include <math.h>


Tremolo::Tremolo() //Constructor
{
    this->modDepth = 0.75;
    this->modFreq = 100;
    this->modAmp = 0.5;
}


void Tremolo::setModFreq(float modFreq) {
  this->modFreq = modFreq;
}


void Tremolo::setModDepth(float modDepth) {
  this->modDepth = modDepth;
}


void Tremolo::process()
{
  for (bufIndex = 0; bufIndex < FRAMESPERBUFFER * CHANNELS; bufIndex++) {

    buffer[bufIndex] = buffer[bufIndex] * (float)(modAmp * sin(modFreq * SAMPLERATE * 2*M_PI) *modDepth);
  }
}
