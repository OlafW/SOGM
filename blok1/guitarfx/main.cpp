#include "amplifier.h"
#include "tremolo.h"
#include "reverser.h"
#include <iostream>


enum{ARG_NAME = 0, ARG_LEVEL, ARG_MOD_FREQ, ARG_MOD_DEPTH, NUM_ARGS};

int main(int argc, char* argv[])
{

  //Audio_IO audiostream;
  Amplifier*  effect[3];

  effect[0] = new Amplifier;
  effect[1] = new Tremolo;
  effect[2] = new Reverser;


  effect[0]->audioSetup();

  while(true) {
  effect[0]->readSamples();
  effect[0]->process();
  effect[0]->writeSamples();
}
  return 0;

} //Main
