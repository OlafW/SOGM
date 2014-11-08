#include "amplifier.h"


void Amplifier::setLevel(float level) {
  this->level = level;
}


float Amplifier::showLevel() {

  return level;
}


void Amplifier::readSamples(float buffer[]) {
  this->buffer = buffer;

}


void Amplifier::processSamples() {
  for (int i = 0; i<BUFFERSIZE; i++) {
    buffer[i] = buffer[i] * level;
  }

}


float* Amplifier::writeSamples() {

  return buffer;
}
