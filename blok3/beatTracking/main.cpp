#include <fstream>
#include "audio_io.h"
#include "sndfile_io.h"
#include "beattracking.h"

#define SAMPLERATE	44100
#define CHANNELS	1
#define N  1024 // Framesize

int main(int argc, char** argv) {
    // float* buffer = new float[N];
    // Start audiostream
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
    sndfile.readFile("./testsig.wav");
    unsigned long bufSize = sndfile.getBufferSize();
    int step = 64;
    float threshold = 0.62;

    float *y = normalize(sndfile.getBuffer(), bufSize);
    y = autoCorrelate(sndfile.getBuffer(), bufSize, step);
    float period = findPeriod(y, bufSize/step, threshold);
    std::cout << "Period in samples: " << period << std::endl;
    std::cout << "Period (s): " << period / SAMPLERATE << std::endl;

    std::ofstream plot;
    plot.open("plot.txt");
    for (int i=0; i<N; i++) {
        plot << y[i] << std::endl;
    }

    plot.close();
    //audioStream.finalise();
    //delete[] buffer;
    delete[] y;
    return 0;
}

/*

make
beatTracker
gnuplot
plot "plot.txt" with lines

*/
