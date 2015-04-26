#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

float prevX = 0;
float prevY = 0;

float filter(float x) {
	float y = 0.5*prevY + 0.25*x + 0.25*prevX;

	prevX = x;
	prevY = y;

	return y;
}


int main() {

	return 0;
}
