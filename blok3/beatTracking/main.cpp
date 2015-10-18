/*
    Beat tracking algorithm
    Example input: beatTracker testsig.wav 0.95 128
*/

#include <fstream>
#include "audio_io.h"
#include "sndfile_io.h"
#include "beattracking.h"

#define SAMPLERATE	44100
#define CHANNELS	1
#define N  1024     // Framesize

enum {ARG_NAME=0, ARG_PATH, ARG_TH, ARG_STEP, ARG_C};

int main(int argc, char** argv) {
    if (argc != ARG_C) {
        std::cout << "Usage: [audiofile path] [peak threshold] [stepsize]" << std::endl;
        return -1;
    }
    string path = argv[ARG_PATH];
    float peakThreshold = atof(argv[ARG_TH]);
    int step = atoi(argv[ARG_STEP]);

    // //Start audiostream
    // float* buffer = new float[N];
    // Audio_IO audioStream(SAMPLERATE, CHANNELS);
    // int input_device;
    // audioStream.set_mode(AUDIO_IO_READONLY);
    // audioStream.set_framesperbuffer(N);
    // audioStream.initialise();
    // audioStream.list_devices();
    // std::cout << "\nGive input device number: ";
    // std::cin >> input_device;
    // audioStream.set_input_device(input_device);
    // audioStream.start_server();
    // audioStream.read(buffer);   //Blocking I/O

    SNDFile sndfile;
    sndfile.readFile(path);
    unsigned long bufSize = sndfile.getBufferSize();

    float* x_norm = normalize(sndfile.getBuffer(), bufSize);
    float* y = autoCorrelate(x_norm, bufSize, step);
    float period = findPeriod(y, bufSize, peakThreshold);
    float bpm = 1.0 / (period / SAMPLERATE) * 60;
    std::cout << "BPM: " << bpm << std::endl;

    // std::ofstream plot;
    // plot.open("plot.txt");
    // for (unsigned long i=0; i<bufSize; i++) {
    //     plot << y[i] << std::endl;
    // }
    // plot.close();

    //audioStream.finalise();
    //delete[] buffer;
    delete[] x_norm;
    delete[] y;
    return 0;
}
