#include "audio_io.h"

int main() {

	audioIO audiofile;
	string path = "/Users/olafwisselink/Code/SOGM/blok3/fft_test/kalimbaloop.wav";

	try {
		audiofile.readFile(path);
		audiofile.writeFile();
	}

	catch(int error) {
		if (error == -1) {
			cout << "audioIO: ";
			cout << "Error opening file" << endl;
		}
		if (error == -2) {
			cout << "audioIO: ";
			cout << "Error writing file" << endl;
		}
	}

	return 0;
}
