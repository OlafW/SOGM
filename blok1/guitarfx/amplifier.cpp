#include "amplifier.h"

Amplifier::Amplifier() //Constructor
{
    this->level=1;
    bufIndex = 0;
}


void Amplifier::setLevel(float level)
{
  this->level = level;
}

void Amplifier::readSamples()
{
  audiostream.read(buffer);
}


void Amplifier::process()
{
    for (int bufIndex = 0; bufIndex < FRAMESPERBUFFER * CHANNELS; bufIndex++) {
    buffer[bufIndex] = buffer[bufIndex] * level;
    }
}


void Amplifier::writeSamples()
{
  audiostream.write(buffer);
}
