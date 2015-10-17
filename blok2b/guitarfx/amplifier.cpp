#include "amplifier.h"
#include <iostream>
using namespace std;

Amplifier::Amplifier() //Constructor
{
    this->level=1;
    bufIndex = 0;
}


// Amplifier::~Amplifier() //Destructor
// {
//
// }


void Amplifier::setLevel(float level)
{
  this->level = level;
}


void Amplifier::startAudio()
{
  audioStream.set_mode(AUDIO_IO_READWRITE);
  audioStream.set_samplerate(sampleRate);
  audioStream.set_nrofchannels(numChannels);
  audioStream.set_framesperbuffer(numFrames);
  audioStream.initialise();
  audioStream.list_devices();
  cout << "\nGive input device number: ";
  cin >> input_device;
  audioStream.set_input_device(input_device);
  cout << "Give output device number: ";
  cin >> output_device;
  audioStream.set_output_device(output_device);
  audioStream.start_server();
}


void Amplifier::readSamples()
{
  audioStream.read(buffer);
}


void Amplifier::process()
{
    for (int bufIndex = 0; bufIndex < numFrames * numChannels; bufIndex++) {
    buffer[bufIndex] = buffer[bufIndex] * level;
    }
}


void Amplifier::writeSamples()
{
  audioStream.write(buffer);
}


void Amplifier::stopAudio()
{
  audioStream.finalise();
}
