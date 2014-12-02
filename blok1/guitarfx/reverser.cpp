#include "reverser.h"


Reverser::Reverser() //Constructor
{
    Amplifier();
}


void Reverser::process()
{
  for (int i = 0; i < BUFFERSIZE; i++) {
  buffer[i] = buffer[BUFFERSIZE-i];
  }

  cout << "Reverser: " << "processing samples" << endl;
}
