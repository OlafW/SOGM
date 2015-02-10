#include <iostream>
#include <math.h>
#include <complex>


double amp = 0;
double freq = 0.0;
int times = 100;

std::complex<double> i(0.0, 1.0);
std::complex<double> z;


double lowpass(double freq) {
    z = exp(-i * freq);
    amp = (std::sqrt( std::pow( 1 + std::real(z), 2.0) + std::pow( std::imag(z), 2.0))) * 0.5;

    return amp;
}


double highpass(double freq) {
    z = exp(-i * freq);
    amp = (std::sqrt( std::pow( 1 - std::real(z), 2.0) + std::pow( std::imag(z), 2.0))) * 0.5;

    return amp;
}


int main() {

  for (int n = 0; n<times; n++) {
        std::cout << highpass(freq) << std::endl;
        freq += (M_PI/times);
  }

  return 0;
}

/*
make fir
fir -> firplot.txt
gnuplot
plot "firplot.txt" with lines
*/
