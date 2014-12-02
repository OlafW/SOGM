#include <iostream>
#include <math.h>
using namespace std;


int main()
{
	float sampleRate = 48000;
	float freq = 480;
	float step = sampleRate/freq;
	int nPeriod = 5;
	
	for(int i=0; i<step*nPeriod; i++) {
		float val = sin(i* 2*M_PI / step);
		
		if(val > 0) {
			val = 0.99;
		}
		else {
			val = 0;
		}
		cout << val << endl;	
	}
}

/*
g++ -o square square.cpp
square > square.txt
gnuplot
plot "square.txt" with lines
*/