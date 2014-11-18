#ifndef _Reverser_
#define _Reverser_

#include "amplifier.h"


class Reverser : public Amplifier {

public:
  Reverser();
  void process();

private:
  float* revBuffer;

}; //Reverser class, reversed een buffer

#endif
