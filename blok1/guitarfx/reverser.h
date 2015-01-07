#ifndef _Reverser_
#define _Reverser_

#include "amplifier.h"
#include <iostream>

using namespace std;


class Reverser : public Amplifier {

public:
  Reverser();
  void process();

private:
  //float revBuffer[sampleRate * numSeconds * numChannels];

};

#endif
