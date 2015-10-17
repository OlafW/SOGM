#include "beattracking.h"

float* autoCorrelate(float* x, unsigned long N, int step) {
    float *y = new float[N];
    float sum;

    for (unsigned long i=0; i<N; i+=step) {
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
        if (x[i] > peak) {
            peak = x[i];
        }
    }
    std::cout << "Peak: " << peak << std::endl;

    //2. Find all peaks within range
    threshold = th * peak;
    for (unsigned long i=0; i<N; i++) {
        if (x[i] > threshold) {
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

    peakIndex.clear();
    return avgPeriod;
}

float* normalize(float* x, unsigned long N) {
    float* y = new float[N];
    float max = 0;
    float gain = 0;

    for (unsigned long i=0; i<N; i++) {
        float abs_x = sqrt(x[i]*x[i]);
        if (abs_x > max) {
            max = abs_x;
        }
    }
    gain = 1.0 / max;
    for (unsigned long i=0; i<N; i++) {
        y[i] = x[i] * gain;
    }
    return y;
}

float RMS(float* x, unsigned long N) {
    float rms = 0.0;

    for (unsigned long i=0; i<N; i++) {
        rms += x[i]*x[i];  //Get squared
    }
    rms /= N;  //Get mean
    rms = sqrt(rms);  //Get root

    return rms;
}
