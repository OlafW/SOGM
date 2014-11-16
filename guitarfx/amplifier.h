#ifndef _AMPLIFIER_H_
#define _AMPLIFIER_H_

#include <iostream>

using namespace std;


class Amplifier {

public:
  Amplifier();
  void setLevel(float level);
  void showLevel();
  void process();

private:
  float level;

}; //Amplifier class

#endif
