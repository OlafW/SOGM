#include "amplifier.h"
#include <iostream>


enum{ARG_NAME = 0, ARG_LEVEL, NUM_ARGS};

float newLevel;

int main(int argc, char* argv[]) {

  if(argc != NUM_ARGS) {
    cout << "Give amplifier level" << endl;
    return -1;
  }

  newLevel = atof(argv[ARG_LEVEL]);

  Amplifier amp;
  amp.setLevel(newLevel);
  cout << "Amplifier level: " << amp.showLevel() << endl;

  return 0;

} //Main programma