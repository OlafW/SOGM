/*
Simple FIRsystem amplitude response calculation of
lowpass and highpass filter
*/


#include <iostream>
#include <complex>
#include <math.h>

double freq = 0.0;
double amp = 0.0;
int count = 100;

std::complex<double> i(0.0, 1.0);
std::complex<double> z;


double lowpass(double freq) {

    z = std::exp(-i * freq);
    amp = std::sqrt( std::pow(1 + std::real(z), 2.0) + std::pow( std::imag(z), 2.0) ) * 0.5;

    return amp;
}


double highpass(double freq) {

    z = std::exp(-i * freq);
    amp = std::sqrt( std::pow(1 - std::real(z), 2.0) + std::pow( std::imag(z), 2.0) ) * 0.5;

    return amp;
}


int main(int argc, char* argv[]) {

  for (int i = 0; i<count; i++) {

      std::cout << highpass(freq) << std::endl;
      freq += (M_PI/count);
  }

return 0;
}

/*
make fir
fir -> firplot.txt
gnuplot
plot "firplot.txt" with lines
*/
