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
  if (argc != 2) {
    cout << "-guitarfx: error" << endl;
    cout << "Give amplifier level" << endl;
    return -1;
  }

  tempLevel = atof(argv[ARG_LEVEL]);

  Amplifier*  effect[3];
  effect[1] = new Tremolo;
  effect[2] = new Reverser;

  effect[1]->setLevel(tempLevel);
  effect[1]->showLevel();
  cout << "Tremolo: ";
  effect[1]->readSamples();
  effect[1]->process();
  cout << "Tremolo: ";
  effect[1]->writeSamples();

  cout << "Reverser: ";
  effect[2]->readSamples();
  effect[2]->process();
  cout << "Reverser: ";
  effect[2]->writeSamples();

  return 0;
} //Main enzo
