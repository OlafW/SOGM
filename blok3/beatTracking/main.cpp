#include <fstream>
#include "audio_io.h"
#include "sndfile_io.h"
#include "beattracking.h"

#define SAMPLERATE	44100
#define CHANNELS	1
#define N  1024 // Framesize

int main(int argc, char** argv) {
    //float* buffer = new float[N];

    // Audio_IO stream(SAMPLERATE, CHANNELS);
    // int input_device;
    // stream.set_mode(AUDIO_IO_READONLY);
    // stream.set_framesperbuffer(N);
    // stream.initialise();
    // stream.list_devices();
    // std::cout << "\nGive input device number: ";
    // std::cin >> input_device;
    // stream.set_input_device(input_device);
    // stream.start_server();
    // audioStream.read(buffer);

    SNDFile sndfile;
    sndfile.readFile("./testsig.wav");
    unsigned long bufferSize = sndfile.getBufferSize();
    int step = 64;
    float threshold = 0.62;

    float* y = autoCorrelate(sndfile.getBuffer(), bufferSize, step);
    float period = findPeriod(y, bufferSize/step, threshold);
    std::cout << "Period in samples: " << period << std::endl;
    std::cout << "Period (s): " << period / SAMPLERATE << std::endl;
    std::cout << "Frequency: " << 1.0 / (period / SAMPLERATE) << std::endl;

    std::ofstream plot;
    plot.open("plot.txt");
    for (int i=0; i<bufferSize; i++) {
        plot << y[i] << std::endl;
    }

    plot.close();
    //audioStream.finalise();
    delete[] y;
    //delete[] buffer;
    return 0;
}

/*

make
beatTracker
gnuplot
plot "plot.txt" with lines

*/
