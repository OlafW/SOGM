#ifndef _BIQUAD_HPP_
#define _BIQUAD_HPP_

#include "audioFxConstants.hpp"

enum BiquadMode {LOWPASS=0, HIGHPASS, BANDPASS, NOTCH, LOWSHELF, HIGHSHELF, NUM_MODES};

class Biquad {
public:
	Biquad();
	Biquad(int mode, float freq, float Q, float gain);
	void process(float* buffer);
	void calculateCoefficients(int mode, float freq, float Q, float gain);

	void setMode(int mode);
	void setFrequency(float freq);
	void setQ(float q);

private:
	double y[2];
	double x[2];

	double a0, a1, a2;
	double b1, b2;

	int mode;
	float freq;
	float Q;
	float gain;
};

#endif
