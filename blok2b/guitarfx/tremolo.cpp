#include "tremolo.h"
#include <math.h>


Tremolo::Tremolo() //Constructor
{
    Amplifier();
    this->modDepth = 0.5;
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
  for (bufIndex = 0; bufIndex < numFrames * numChannels; bufIndex++) {

    buffer[bufIndex] = buffer[bufIndex] * (((sin( sampleIndex * modFreq/sampleRate * 2*M_PI ) *modDepth) + 1) * 0.5);
    sampleIndex++;
  }
}
