#include "beattracking.h"

float* autoCorrelate(float* x, unsigned long N, int step) {
    float *y = new float[N/step];
    float sum;

    for (unsigned long i=0; i<N-step; i+=step) {
        sum = 0;
        for (unsigned long j=0; j<N-i; j+=step) {
            sum += x[j] * x[j+i];
        }
        sum = sqrt(sum*sum);    //Absolute value
        y[i] = sum / (N-i); //Normalise
    }
    return y;
}

float findPeriod(float* x, unsigned long N, float th) {
    float peak = 0;
    vector<unsigned long> peakIndex;
    float threshold;

    //1. Find highest peak
    for (unsigned long i=0; i<N; i++) {
        if (x[i] >= peak) {
            peak = x[i];
        }
    }
    std::cout << "Peak: " << peak << std::endl;

    //2. Find all peaks within range
    threshold = th*peak;
    for (unsigned long i=0; i<N; i++) {
        if (x[i] >= threshold) {
            peakIndex.push_back(i);
        }
    }
    std::cout << "Peakcount: " << peakIndex.size() << std::endl;

    //3. Find average period in samples according to sample indexes of peaks
    float avgPeriod = 0;

    for (unsigned long i=0; i<peakIndex.size()-1; i++) {
        avgPeriod += peakIndex[i+1] - peakIndex[i];
    }
    avgPeriod /= peakIndex.size();

    return avgPeriod;
}
