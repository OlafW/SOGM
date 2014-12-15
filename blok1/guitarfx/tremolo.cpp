#include "tremolo.h"
#include <math.h>


Tremolo::Tremolo() //Constructor
{
    Amplifier();
    this->modDepth = 1;
    this->modFreq = 5;
    sampleIndex = 0;
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

    buffer[bufIndex] = buffer[bufIndex] * (sin( sampleIndex * modFreq/SAMPLERATE * 2*M_PI ) *modDepth);
    sampleIndex++;
  }
}
