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

  Amplifier amp;

  amp.setLevel(tempLevel);
  amp.showLevel();
  cout << "Amplifier: ";
  amp.readSamples();
  amp.process();
  cout << "Amplifier: ";
  amp.writeSamples();

  Tremolo trem;
  
  cout << "Tremolo: ";
  trem.readSamples();
  trem.process();
  cout << "Tremolo: ";
  trem.writeSamples();

  return 0;
} //Main
