#include "reverser.h"


Reverser::Reverser() //Constructor
{
  Amplifier();
  cout << (sampleRate * numSeconds * numChannels) << endl;
}


void Reverser::process()
{
  for (bufIndex = 0; bufIndex < (sampleRate * numSeconds * numChannels); bufIndex++) {

        revBuffer[ (sampleRate * numSeconds * numChannels) - bufIndex] = buffer[bufIndex];
  }


  for (bufIndex = 0; bufIndex < (sampleRate * numSeconds * numChannels); bufIndex++) {

        buffer[bufIndex] = revBuffer[bufIndex];
        sleep(10);
  }
}
