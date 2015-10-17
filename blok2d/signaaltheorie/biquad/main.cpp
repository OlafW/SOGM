#include "biquad.h"
#include "io-aiff/rdaiff.hpp"
#include "io-aiff/wraiff.hpp"

int main() {

	try {
		RDAIFF inFile("afrikaanBeat.aiff");
		int channels = inFile.channels();
		WRAIFF outFile("out.aiff",inFile.samplerate(), channels, inFile.bits());
		float* frame = new float[channels];	//One sampleframe of buffer

		Biquad** biquad = new Biquad*[channels];	//Set of biquad filters per channel
		double coeffs[5] = {0.118415308697835, 0.23683061739567, 0.118415308697835, -1.4628922200703627, 0.9365534548617026};
		for (int ch=0; ch<channels; ch++) {
			biquad[ch] = new Biquad(coeffs);
		}

		inFile.info(cout);
		for (long long fr=0; fr<inFile.frames(); fr++) {
			inFile.read(frame,1);	//Read a single frame

			for (int ch=0; ch<channels; ch++) {	//All channels
				frame[ch] = biquad[ch]->process(frame[ch]);
			}
			outFile.write(frame,1);	//Write single frame
		}
		delete[] frame;
		delete[] biquad;
		outFile.info(cout);
		cout << "Done" << endl;
	}

	catch (const char* err_txt) {
		cout << err_txt << endl;
	}

	return 0;
}
