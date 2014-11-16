#include "delay.h"

Delay::Delay() //Constructor
{
    Amplifier();
    this->delayTime = 250;
    this->feedback = 0.5;
}

void Delay::setDelayTime(float delayTime)
{
  this->delayTime = delayTime;
}



void Delay::setFeedback(float feedback)
{
  this->feedback = feedback;
}


void Delay::process() {
  cout << "Delay: " << "delayTime = " << delayTime << endl;
  cout << "Delay: " << "feedback = " << feedback << endl;
  cout << "Delay: " << "processing...." << endl;

}
