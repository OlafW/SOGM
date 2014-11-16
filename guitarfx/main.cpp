#include "amplifier.h"
#include "tremolo.h"
#include <iostream>


enum{ARG_NAME = 0, ARG_LEVEL, ARG_MOD_FREQ, ARG_MOD_DEPTH, NUM_ARGS};

float tempLevel;
float tempModFreq;
float tempModDepth;

int main(int argc, char* argv[])
{
  tempLevel = atof(argv[ARG_LEVEL]);
  
  Amplifier amp;
  Tremolo trem;

  amp.setLevel(tempLevel);
  amp.showLevel();
  trem.process();

  return 0;
} //Main
