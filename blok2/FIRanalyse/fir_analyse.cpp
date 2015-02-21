#include <iostream>
#include <complex>
#include <math.h>

enum{ARG_NAME=0, ARG_ORDER, ARG_COEFF, NUM_ARGS};

std::complex<double> i(0.0, 1.0);
std::complex<double> z;


float firAnalyse(double freq, float coeff[], int numOrder) {

    float H = 0.0;
    double real = 0.0;
    double imag = 0.0;

    for (int n = 0; n<numOrder; n++) {

        z = std::exp(-i * freq * double(n));
        real += coeff[n]*std::real(z);
        imag += coeff[n]*std::imag(z);
    }

    H = std::sqrt(std::pow(real, 2.0) + std::pow(imag, 2.0));
    return H;
}


int main(int argc, char* argv[]) {

  int numOrder;
  int numFreq = 100;
  double freq = 0.0;

  std::cout << "Give number of orders: ";
  std::cin >> numOrder;
  float coeff[numOrder];

  for (int i=0; i<numOrder; i++) {
      std::cout << "Give coefficient " << i+1 << ": ";
      std::cin >> coeff[i];
  }

  for (int i=0; i<numFreq; i++) {
      std::cout << firAnalyse(freq, coeff, numOrder) << std::endl;
      freq += (M_PI/numFreq);
  }

  return 0;
}
