/*
    Beat tracking algorithm
    Usage: [audiofile path] [stepsize] [peak threshold] [inhib_fb]
    Example input: beatTracker sound/testsig.wav 128 0.945 4
*/

#include <fstream>
#include "sndfile_io.h"
#include "beattracking.h"

enum {ARG_NAME=0, ARG_PATH, ARG_STEP, ARG_TH, ARG_FB, ARG_C};

int main(int argc, char** argv) {
    if (argc != ARG_C) {
        std::cout << "Usage: [audiofile path] [stepsize] [peak threshold] [inhibitory feedback factor]" << std::endl;
        std::cout << "Example input: beatTracker sound/testsig.wav 128 0.945 4" << std::endl;
        return -1;
    }
    string path = argv[ARG_PATH];
    int step = atoi(argv[ARG_STEP]);
    float threshold = atof(argv[ARG_TH]);
    float fb = atof(argv[ARG_FB]);

    //Load soundfile
    SNDFile sndfile;
    sndfile.readFile(path);
    unsigned long N = sndfile.getBufferSize();
    const int FS = sndfile.getSampleRate();

    float* x = normalize(sndfile.getBuffer(), N);
    float* y = autoCorrelate(x, N, step);
    float period = findPeriod(y, N, threshold, fb);
    // float deviation = stdDeviation(x, N);
    // std::cout << "Deviation: " << deviation << std::endl;

    float BPM = 1.0 / (period / FS) * 60;
    std::cout << "BPM: " << BPM << std::endl;

    std::ofstream plot;
    plot.open("plot.txt");
    for (unsigned long i=0; i<N; i++) {
        plot << y[i] << std::endl;
    }
    plot.close();

    delete[] x;
    delete[] y;
    return 0;
}

/*
make
beatTracker sound/testsig.wav 128 0.94 4
gnuplot
plot "plot.txt" with lines
*/
