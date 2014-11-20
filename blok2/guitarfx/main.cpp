#include "amplifier.h"
#include "tremolo.h"
#include "reverser.h"
#include <iostream>


enum{ARG_NAME = 0, ARG_LEVEL, ARG_MOD_FREQ, ARG_MOD_DEPTH, NUM_ARGS};

float tempLevel;
float tempModFreq;
float tempModDepth;

int main(int argc, char* argv[])
{
  tempLevel = atof(argv[ARG_LEVEL]);

  Amplifier *amp = new Amplifier;

  amp->setLevel(tempLevel);
  amp->showLevel();
  amp->readSamples();
  amp->process();
  amp->writeSamples();

  Tremolo trem;
  trem.readSamples();
  trem.process();
  trem.writeSamples();

  Reverser rev;
  rev.readSamples();
  rev.process();
  rev.writeSamples();


  return 0;
} //Main
