/*
    Beat tracking algorithm work in progress.
    Based on finding average period of peaks in autocorrelated signal.
    Peaks are found using a threshold based on inhibitory feedback and weighting.

    Usage: [audiofile path] [autocorrelation stepsize] [peak threshold min] [peak threshold max] [feedback discharge].
    Example input 1: beatTracker sound/bleep_120bpm.wav 128 0.92 1.7 0.998
    Example input 2: beatTracker sound/drum_140bpm.wav 64 0.15 15 0.998
    Example input 3: beatTracker sound/perc_92bpm.wav 512 0.1 25 0.9998
    Example input 4: beatTracker sound/shaker_102bpm.wav 1024 0.1 10 0.9998
*/

#include <stdlib.h>
#include <fstream>
#include "sndfile_io.h"
#include "beattracking.h"

enum {ARG_NAME=0, ARG_PATH, ARG_STEP, ARG_TH_MIN, ARG_TH_MAX, ARG_DISCHARGE, ARG_C};

int main(int argc, char** argv) {
    if (argc != ARG_C) {
        std::cout << "Usage: [audiofile path] [stepsize] [threshold min] [threshold max] [discharge]" << std::endl;
        std::cout << "Example input: beatTracker sound/bleep_120bpm.wav 128 0.92 1.7 0.998" << std::endl;
        return -1;
    }
    string path = argv[ARG_PATH];
    int step = atoi(argv[ARG_STEP]);    //Power of 2?
    float th_min = atof(argv[ARG_TH_MIN]);
    float th_max = atof(argv[ARG_TH_MAX]);
    float discharge = atof(argv[ARG_DISCHARGE]);

    if (th_min <= 0 || th_min >= 1 || th_max < 1 || discharge <= 0 || discharge >= 1) {
        std::cout << "Error: ";
        std::cout << "\t 0 > th_min < 1" << std::endl;
        std::cout << "\t 1 >= th_max" << std::endl;
        std::cout << "\t 0 > discharge < 1" << std::endl;
        return -1;
    }

    //Load soundfile
    SNDFile sndfile;
    if (sndfile.readFile(path) < 0) return -1;
    unsigned long N = sndfile.getBufferSize();
    int FS = sndfile.getSampleRate();

    float* x = normalize(sndfile.getBuffer(), N);
    float* y = autoCorrelate(x, N, step);
    float period = findPeriod(y, N, th_min, th_max, discharge);

    float BPM = 1.0 / (period / FS) * 60.0;
    std::cout << "BPM: " << BPM << std::endl;

    std::ofstream plot; //Test plot for autocorrelation
    plot.open("plot.txt");
    for (unsigned long i=0; i<N; i++) {
        plot << y[i] << std::endl;
    }
    plot.close();

    delete[] x;
    delete[] y;
    return 0;
}
