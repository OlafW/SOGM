#include "amplifier.h"


void Amplifier::setLevel(float level) {
  this->level = level;
}


void Amplifier::showLevel() {
  cout << "Amplifier: " << "amplifier level = " << level << endl;
}


void Amplifier::process() {
  cout << "Amplifier: " << "processing..." << endl;
}
