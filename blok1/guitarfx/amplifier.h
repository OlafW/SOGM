#ifndef _AMPLIFIER_H_
#define _AMPLIFIER_H_

#include <iostream>
#include "audio_io.h"

using namespace std;

#define SAMPLERATE  44100
#define CHANNELS  1
#define FRAMESPERBUFFER	1024

class Amplifier : public Audio_IO
{

public:
  Audio_IO audiostream;
  Amplifier();
  void setLevel(float level);
  void readSamples();
  virtual void process();
  void writeSamples();

protected:
  float buffer[FRAMESPERBUFFER * CHANNELS];
  unsigned long bufIndex;

private:
  float level;

}; //Amplifier class

#endif
