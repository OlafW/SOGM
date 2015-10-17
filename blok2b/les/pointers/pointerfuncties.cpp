#include <iostream>
#include <string.h>

using namespace std;

#define SAMPLERATE 48000
#define BUFFERSIZE 10*SAMPLERATE


void process(float* buf)
{
  for (int i = 0; i < BUFFERSIZE; i++) {
    //cout << *(buf+i) << endl;
    cout << buf[i] << endl;  //Zelfde, een array is pointer en vice versa
  }
}



int main()
{
  float* buffer;
  buffer = new float[BUFFERSIZE];

  for (int i = 0; i < BUFFERSIZE; i++) {
    *(buffer+i) = i;
  }

  process(buffer);

  return 0;
}
