#include "amplifier.h"
#include <iostream>


enum{ARG_NAME = 0, ARG_LEVEL, NUM_ARGS};

float newLevel;
float buffer[] = {0, 0.5, 1, 0.5, 0, -0.5, -1, -0.5, 0, 0.5};
float* tempbuffer;

int main(int argc, char* argv[]) {

  if(argc != NUM_ARGS) {
    cout << "Give amplifier level" << endl;
    return -1;
  }

  newLevel = atof(argv[ARG_LEVEL]);

  Amplifier amp;
  cout << "Amplifier level: " << amp.showLevel() << endl;

  amp.setLevel(newLevel);
  amp.readSamples(buffer);
  amp.processSamples();
  tempbuffer = amp.writeSamples();
  for(int i = 0; i <10; i++) {
    cout << tempbuffer[i] << endl;
  }

  return 0;

} //Main
