#include <iostream>
#include "sinewave.h"


int main(int argc, char ** argv) {

  SineWave sine;
  sine.setFrequency(441);
  sine.setAmplitude(1);
  sine.setSampleRate(44100);
  sine.setDuration(1);
  sine.generate();

  return 0;
}
