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
        y[i] = sum / ((N - i) / float(step)); //Normalise
    }
    return y;
}

float findPeriod(float* x, unsigned long N, float th) {    //Assumes x = correlated
    float peak = 0, threshold = 0;
    vector<unsigned long> peakIndex;

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
        else {
            x[i] = 0;   //For plotting
        }
    }
    std::cout << "Peakcount: " << peakIndex.size() << std::endl;

    //3. Find average period in samples according to sample indexes of peaks
    float avgPeriod = 0;
    for (unsigned long i=0; i<peakIndex.size()-1; i++) {
        avgPeriod += peakIndex[i+1] - peakIndex[i];
        //std::cout << "Period: " << peakIndex[i+1] - peakIndex[i] << std::endl;
    }
    avgPeriod /= (peakIndex.size() - 1);

    peakIndex.clear();
    return avgPeriod;
}

float stdDeviation(float* x, unsigned long N) {
    float mean = 0, variance = 0, deviation = 0;

    for (unsigned long i=0; i<N; i++) {
        mean += x[i];
    }
    mean /= N;

    for (unsigned long i=0; i<N; i++) {
        variance += pow((x[i] - mean), 2);
    }
    variance /= N;
    deviation = sqrt(variance);

    return deviation;
}

float* normalize(float* x, unsigned long N) {
    float* y = new float[N];
    float max = 0, gain = 0, sqval = 0;

    for (unsigned long i=0; i<N; i++) {
        sqval = x[i]*x[i];
        if (sqval > max) {
            max = sqval;
        }
    }
    gain = 1.0 / sqrt(max);
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
