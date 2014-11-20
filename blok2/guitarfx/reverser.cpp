#include "reverser.h"


Reverser::Reverser() //Constructor
{
    Amplifier();
}


void Reverser::process()
{
  revBuffer = getBuffer();
  for (int i = 0; i < BUFFERSIZE; i++) {
  revBuffer[i] = revBuffer[BUFFERSIZE-i];
  }

  cout << "Reverser: " << "processing...." << endl;
}
