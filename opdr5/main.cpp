#include <iostream>
#include <cstdlib>
#include "sinewave.h"



int main(int argc, char *argv[]) {

  enum{ARG_NAME = 0, ARG_FREQ, ARG_AMP, ARG_DUR, NUM_ARGS};

  if (argc != NUM_ARGS || atoi(argv[ARG_FREQ]) < 1 ||
      atof(argv[ARG_AMP]) > 1 || atof(argv[ARG_DUR]) <= 0 ) {
    cout << "Give: \n"
          "- frequency(> 1) \n" <<
          "- amplitude(<= 1) \n" <<
          "- duration(> 0) \n" <<
          "  default sampleRate = 44100" << endl;
  }

  else {

  SineWave sine;
  float* tempSize;

  sine.setFrequency(atoi(argv[ARG_FREQ]));
  sine.setAmplitude(atof(argv[ARG_AMP]));
  sine.setSampleRate();
  sine.setDuration(atof(argv[ARG_DUR]));

  tempSize = sine.generate();
  for (int i = 0; i < sine.setSampleRate() *
    sine.setDuration(atof(argv[ARG_DUR])); i++) {
    cout << tempSize[i] << endl;
  }

  }
  return 0;
}
