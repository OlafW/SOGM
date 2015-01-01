#include "amplifier.h"
#include "tremolo.h"
#include "reverser.h"
#include <iostream>


enum{ARG_NAME = 0, ARG_LEVEL, ARG_MOD_FREQ, ARG_MOD_DEPTH, NUM_ARGS};

int main(int argc, char* argv[])
{

  Amplifier* effect[3];

  effect[0] = new Amplifier;
  effect[1] = new Tremolo;
  effect[2] = new Reverser;


  effect[1]->startAudio();

  while(true) {
  effect[1]->readSamples();
  effect[1]->process();
  effect[1]->writeSamples();
}

  effect[1]->stopAudio();

  for (int i = 0; i<3; i++) {
    delete effect[i];
  }


  return 0;
} //Main
