#include "tremolo.h"
#include <math.h>


Tremolo::Tremolo() //Constructor
{
    Amplifier();
    this->modDepth = 0.75;
    this->modFreq = 5;
}


void Tremolo::setModFreq(float modFreq) {
  this->modFreq = modFreq;
}


void Tremolo::setModDepth(float modDepth) {
  this->modDepth = modDepth;
}


void Tremolo::process()
{
  for (int i = 0; i < BUFFERSIZE; i++) {
    modAmp = sin(i* 2*M_PI / (SAMPLERATE/modFreq) ) * modDepth;
    buffer[i] = buffer[i] * modAmp;
  }

  cout << "Tremolo: " << "modDepth = " << modDepth << endl;
  cout << "Tremolo: " << "modFreq = " << modFreq << endl;
  cout << "Tremolo: " << "processing samples" << endl;
}
