#include "amplifier.h"
#include "tremolo.h"
#include <iostream>


enum{ARG_NAME = 0, ARG_LEVEL, NUM_ARGS};


int main(int argc, char* argv[]) {

  if(argc != NUM_ARGS) {
    cout << "Give amplifier level" << endl;
    return -1;
  }

  float tempLevel = atof(argv[ARG_LEVEL]);

  Amplifier amp;
  Tremolo trem;

  amp.setLevel(tempLevel);
  amp.showLevel();
  trem.process();

  return 0;
} //Main
