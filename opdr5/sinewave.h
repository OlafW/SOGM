#include <string>
#include <math.h>
using namespace std;


class SineWave {

private:
  int sampleRate;
  int frequency;
  float amplitude;
  float duration;
  float val;
  float period;

public:
  void setFrequency(int new_freq);
  void setAmplitude(float new_amp);
  void setSampleRate(int new_samplerate);
  void setDuration(float new_dur);
  void generate();
};
