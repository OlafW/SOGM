#ifndef _TREMOLO_H_
#define _TREMOLO_H_

#include "amplifier.h"

class Tremolo : public Amplifier {

public:
  Tremolo();
  void setModFreq(float modFreq);
  void setModDepth(float modDepth);
  void process();

private:
  float modFreq;
  float modDepth;
  unsigned long sampleIndex;

}; //Tremolo class

#endif
