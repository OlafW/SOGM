#include "reverser.h"


Reverser::Reverser() //Constructor
{
  Amplifier();
}


void Reverser::process()
{
  for (bufIndex = 0; bufIndex < (sampleRate * numSeconds * numChannels); bufIndex++) {
        //revBuffer[ (sampleRate * numSeconds * numChannels) - bufIndex] = buffer[bufIndex];
        //Werkt niet....
  }
  
}
