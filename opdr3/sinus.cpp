#include <iostream>
#include <math.h>
using namespace std;

#define PI 3.14159265

int main()
{
	float sampleRate = 48000;
	float freq = 480;
	float stap = sampleRate/freq;
	
	for(float i=0; i<stap; i++) {
		cout <<	sin (i* (PI / (stap*0.5))) << endl;	
	}
	
	return 0;
}
