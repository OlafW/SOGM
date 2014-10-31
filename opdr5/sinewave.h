#include <string>
#include <math.h>
using namespace std;


class SineWave {

private:
  int sampleRate;
  int frequency;
  float amplitude;
  float duration;
  float period;
  float* val;

public:
  void setFrequency(int new_freq);
  void setAmplitude(float new_amp);
  int setSampleRate(int new_samplerate=44100);
  float setDuration(float new_dur);
  float* generate();
};
