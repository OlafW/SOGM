#ifndef _AMPLIFIER_H_
#define _AMPLIFIER_H_

#include <iostream>

using namespace std;

#define BUFFERSIZE 10

class Amplifier {

public:
  Amplifier();
  void setLevel(float level);
  void showLevel();
  void readSamples();
  void process();
  void writeSamples();
  float* getBuffer();

private:
  float level;
  float* buffer;

}; //Amplifier class

#endif
