#ifndef _DELAY_H_
#define _DELAY_H_

#include "amplifier.h"


class Delay : public Amplifier {

public:
  Delay();
  void setDelayTime(float delayTime);
  void setFeedback(float feedback);
  void process();

private:
  float delayTime;
  float feedback;

}; //Delay class

#endif
