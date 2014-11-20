#include <iostream>
#include <math.h>
using namespace std;



int main()
{
	float sampleRate = 48000;
	float freq = 480;
	float step = sampleRate/freq;
	
	for(int i=0; i<step; i++) {
		float val = sin(i* 2*M_PI / step);
		cout << val << endl;	
	}
}
