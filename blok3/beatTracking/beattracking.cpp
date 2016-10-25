#include "beattracking.h"

float* autoCorrelate(float* x, unsigned long N) {
    float *y = new float[N];
    float sum;

    for (unsigned long n=0; n<N; n++) {
        sum = 0;
        for (unsigned long m=0; m<N-n; m++) {
            sum += x[m] * x[m + n];
        }
        sum = sqrt(sum*sum);   // Absolute value
        y[n] = sum / (N - n); // Normalise
    }
    return y;
}

float findPeriod(float* x, unsigned long N, float th_min, float th_max, float discharge) { //Assumes x = correlated
    float peak = 0, threshold = 0, fb_val = th_min;
    vector<unsigned long> peakIndex;

    //1. Find highest peak
    for (unsigned long i=0; i<N; i++) {
        if (x[i] > peak) {
            peak = x[i];
        }
    }
    std::cout << "Peak: " << peak << std::endl;

    //2. Find all peaks based on threshold and inhibitory feedback factor
    for (unsigned long i=0; i<N; i++) {
        threshold = peak * fb_val;
        if (x[i] > threshold) {
            peakIndex.push_back(i);
            fb_val = th_max;    //Recharge to maximum threshold
        }
        else if (fb_val > th_min)
                 fb_val *= discharge;  //Discharge to minimum threshold
    }
    std::cout << "Peakcount: " << peakIndex.size() << std::endl;

    //3. Find average period in samples according to weighted sample indexes of peaks
    //   Weighting is based on difference between peak and maximum peak
    float avgPeriod = 0, weight = 1;

    for (unsigned long i=0; i<peakIndex.size()-1; i++) {
        weight = 1.0 - ( 2.0*peak - (x[peakIndex[i+1]] + x[peakIndex[i]]) );
        avgPeriod += weight * (peakIndex[i+1] - peakIndex[i]);
    }
    avgPeriod /= (peakIndex.size() - 1);

    peakIndex.clear();
    return avgPeriod;
}

float stdDeviation(float* x, unsigned long N) {
    float mean = 0, variance = 0, deviation = 0;

    for (unsigned long i=0; i<N; i++) {
        mean += x[i] * x[i];
    }
    mean = sqrt(mean / N);

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
