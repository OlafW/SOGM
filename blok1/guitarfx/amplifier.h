#ifndef _AMPLIFIER_H_
#define _AMPLIFIER_H_

#include <iostream>
#include "audio_io.h"

using namespace std;

#define sampleRate 44100
#define numChannels 1
#define numFrames	1024
#define numSeconds 5

class Amplifier : public Audio_IO
{

public:
  Audio_IO audioStream;
  Amplifier();
  // virtual ~Amplifier();
  void setLevel(float level);
  void startAudio();
  void stopAudio();
  void readSamples();
  virtual void process();
  void writeSamples();

protected:
  float buffer[numFrames * numChannels];
  unsigned long bufIndex;
  int input_device;
  int output_device;

private:
  float level;

}; //Amplifier class

#endif
