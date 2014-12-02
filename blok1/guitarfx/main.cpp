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

  Amplifier*  baseFX[3];
  baseFX[0] = new Amplifier;
  baseFX[1] = new Tremolo;
  baseFX[2] = new Reverser;

  baseFX[1]->setLevel(tempLevel);
  baseFX[1]->showLevel();
  cout << "Tremolo: ";
  baseFX[1]->readSamples();
  baseFX[1]->process();
  cout << "Tremolo: ";
  baseFX[1]->writeSamples();

  cout << "Reverser: ";
  baseFX[2]->readSamples();
  baseFX[2]->process();
  cout << "Reverser: ";
  baseFX[2]->writeSamples();

  return 0;
} //Main
