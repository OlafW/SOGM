#include "sndfile_io.h"

SNDFile::SNDFile() {
	inFile = NULL;
	outFile = NULL;
	buffer = NULL;
	path = NULL;
}

SNDFile::~SNDFile() {
	if (buffer) delete[] buffer;
}

int SNDFile::readFile(string path) {
	this->path = path.c_str();
	inFile = sf_open(this->path, SFM_READ, &sfInfo);

	if (inFile == NULL) {
		std::cout << "Error opening file" << std::endl;
		return -1;
	}

	sampleRate = sfInfo.samplerate;
	channels = sfInfo.channels;
	N = sfInfo.frames;

	buffer = new float[N*channels];

	sf_readf_float(inFile, buffer, N);
	sf_close(inFile);

	return 0;
}

int SNDFile::writeFile(float* buffer, SF_INFO sfInfo, string outName) {
	outFile = sf_open(outName.c_str(), SFM_WRITE, &sfInfo);

	if (outFile == NULL) {
		std::cout << "Error writing file" << std::endl;
		return -1;
	}

	sf_writef_float(outFile, buffer, sfInfo.frames);
	sf_close(outFile);

	return 0;
}

float* SNDFile::getBuffer() {
	return buffer;
}

unsigned long SNDFile::getBufferSize() {
	return N*channels;
}

int SNDFile::getSampleRate() {
	return sampleRate;
}
