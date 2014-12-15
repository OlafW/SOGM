#include "amplifier.h"

Amplifier::Amplifier() //Constructor
{
    this->level=1;
    bufIndex = 0;
}


void Amplifier::setLevel(float level)
{
  this->level = level;
}


void Amplifier::startAudio()
{
  audiostream.set_mode(AUDIO_IO_READWRITE);
  audiostream.set_samplerate(SAMPLERATE);
  audiostream.set_nrofchannels(CHANNELS);
  audiostream.set_framesperbuffer(FRAMESPERBUFFER);

  audiostream.initialise();
  audiostream.list_devices();
  cout << "\nGive input device number: ";
  cin >> input_device;
  audiostream.set_input_device(input_device);
  cout << "Give output device number: ";
  cin >> output_device;
  audiostream.set_output_device(output_device);
  audiostream.start_server();
}


void Amplifier::readSamples()
{
  audiostream.read(buffer);
}


void Amplifier::process()
{
    for (int bufIndex = 0; bufIndex < FRAMESPERBUFFER * CHANNELS; bufIndex++) {
    buffer[bufIndex] = buffer[bufIndex] * level;
    }
}


void Amplifier::writeSamples()
{
  audiostream.write(buffer);
}


void Amplifier::stopAudio()
{
  audiostream.finalise();
}
