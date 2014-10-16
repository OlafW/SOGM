#include <iostream>
#include <math.h>
#include <functional>
using namespace std;


int main() {
	
	int sampleRate = 44100;
	int freq = 440;
	float step = sampleRate/freq;
	float val;
	int nPeriod = 5;
	int times;
	
	for (int i = 0; i < step*nPeriod; i++) {
		val = i/step;
		times += 1;
		if (val > 1) {
			i = 0;	
		}
		if (times == step*nPeriod) {
			break;
		}
		cout << val << endl;
	}		
}

	
/*
g++ -o phasor phasor.cpp
phasor > phasor.txt
gnuplot
plot "phasor.txt" with lines
*/	
