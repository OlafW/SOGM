#include "amplifier.h"

Amplifier::Amplifier() //Constructor
{
    this->level=1;
}


void Amplifier::setLevel(float level)
{
  this->level = level;
}


void Amplifier::showLevel()
{
  cout << "Amplifier: " << "level = " << level << endl;
}


void Amplifier::readSamples()
{
  cout << "reading samples" << endl;

}


void Amplifier::process()
{
  for (int i = 0; i < BUFFERSIZE; i++) {
    buffer[i] = buffer[i] * level;
  }

  cout << "Amplifier: " << "processing samples" << endl;
}


void Amplifier::writeSamples()
{
  cout << "writing samples" << endl;
}
