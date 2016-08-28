#include "audio_io.h"
#include "amplifier.hpp"
#include "tremolo.hpp"
#include "distortion.hpp"
#include "delay.hpp"
#include <signal.h>

Audio_IO audioStream;
bool quit = false;

void startAudio() {
    int input_device = 0;
    int output_device = 1;
    audioStream.set_mode(AUDIO_IO_READWRITE);
    audioStream.set_samplerate(SAMPLERATE);
    audioStream.set_nrofchannels(CHANNELS);
    audioStream.set_framesperbuffer(FRAMES);
    audioStream.initialise();
    audioStream.list_devices();
    // std::cout << "\nGive input device number: ";
    // std::cin >> input_device;
    audioStream.set_input_device(input_device);
    // std::cout << "Give output device number: ";
    // std::cin >> output_device;
    audioStream.set_output_device(output_device);
    audioStream.start_server();
}


void intHandler(int s) {
    quit = true;
    std::cout << "\n" << "quit" << std::endl;
}

int main (int argc, char* argv[]) {
    const unsigned long N = FRAMES * CHANNELS;
    float* buffer = new float[N];
    for (unsigned long n=0; n<N; n++) buffer[n] = 1.0;

    signal (SIGINT, intHandler);

    Amplifier amplifier;
    amplifier.setGain(1.0);
    amplifier.process(buffer);

    Tremolo tremolo;
    tremolo.setModFreq(5.0);
    tremolo.setModDepth(0.5);

    Distortion distortion;
    distortion.setGain(10.0);

    Delay delay(50);
    delay.setDelayTime(1);

    startAudio();

    while (!quit) {
        //audioStream.read(buffer);
        delay.process(buffer);
        //audioStream.write(buffer);
        break;
    }

    audioStream.finalise();
    delete[] buffer;

    return 0;
}
