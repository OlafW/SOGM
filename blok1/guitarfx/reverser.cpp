#include "reverser.h"


Reverser::Reverser() //Constructor
{
}


void Reverser::process()
{
  for (bufIndex = 0; bufIndex < FRAMESPERBUFFER * CHANNELS; bufIndex++) {
  buffer[bufIndex] = buffer[FRAMESPERBUFFER * CHANNELS-bufIndex];
  }

  cout << "Reverser: " << "processing samples" << endl;
}
