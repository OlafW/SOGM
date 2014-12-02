#ifndef _AMPLIFIER_H_
#define _AMPLIFIER_H_

#include <iostream>

using namespace std;

#define CHANNELS 1
#define SAMPLERATE 44100
#define BUFFERSIZE 10 * CHANNELS


class Amplifier {

public:
  Amplifier();
  void setLevel(float level);
  void showLevel();
  void readSamples();
  virtual void process();
  void writeSamples();

protected:
  float buffer[BUFFERSIZE];

private:
  float level;

}; //Amplifier class

#endif
