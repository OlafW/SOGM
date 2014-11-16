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


void Amplifier::process()
{
  cout << "Amplifier: " << "processing..." << endl;
}
