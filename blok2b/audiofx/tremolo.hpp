#ifndef _TREMOLO_H_
#define _TREMOLO_H_

#include "amplifier.hpp"
#include <math.h>

class Tremolo : public Amplifier {

public:
  Tremolo();
  ~Tremolo() {};
  void setModFreq(float modFreq);
  void setModDepth(float modDepth);
  void process(float* buffer);

private:
  float modFreq;
  float modDepth;
  unsigned int phase;
  unsigned int period;
};

#endif
