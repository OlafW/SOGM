#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <string>
#include <sndfile.h>

using namespace std;


enum{ARG_NAME = 0, ARG_PATH, ARG_GAIN, NUM_ARGS};

SF_INFO sfInfo;
SNDFILE* inFile;
SNDFILE* outFile;

char* path;
string outName;
string extension;
float gain;
float maxVal = 0;
float absVal;
int sampleRate;
int channels;
long int numFrames;


int main(int argc, char* argv[]) {

  if (argc != NUM_ARGS || atof(argv[ARG_GAIN]) <= 0 ||
      atof(argv[ARG_GAIN]) > 1 ) {
      cout << "Give: \n"
            "- file path \n"
            "- gain(0 < gain > 1)" << endl;
      return -1;
  }

  path = argv[ARG_PATH];
  gain = atof(argv[ARG_GAIN]);
  inFile = sf_open(path, SFM_READ, &sfInfo);

  if(inFile == NULL) {
    cout << "Error opening file" << endl;
    return -1;
  }

  sampleRate = sfInfo.samplerate;
  channels = sfInfo.channels;
  numFrames = sfInfo.frames;
  cout << "Gain: " << gain << endl;
  cout << "Length: " << float(numFrames/sampleRate) << "s" << endl;
  cout << "Channels: " << channels << endl;
  cout << "Samplerate: " << sampleRate << endl;


  float buffer[numFrames*channels];
  sf_readf_float(inFile, buffer, numFrames);


  for (int i = 0; i < numFrames*channels; i++) {
    if (fabs(buffer[i]) > maxVal) {
      maxVal = fabs(buffer[i]);
    }
  }
  cout << "Peak value: " << 20*log(maxVal) << " dB" << endl;

  for (int i = 0; i < numFrames*channels; i++) {
    buffer[i] = buffer[i] * gain / maxVal;
  }

  outName = path;
  unsigned find_ext = outName.find_last_of(".");
  extension = outName.substr(find_ext);
  outName = outName.substr(0,find_ext);
  outName = outName + "_norm" + extension;

  outFile = sf_open(outName.c_str(), SFM_WRITE, &sfInfo);
  sf_writef_float(outFile, buffer, numFrames);

  sf_close(inFile);
  sf_close(outFile);

  return 0;
}
